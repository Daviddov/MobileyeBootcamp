#include "ServerListeningManager.h"

using namespace cv;

ServerListeningManager::ServerListeningManager(QueueSafe<FrameWrap>& queue, std::condition_variable& condition)
    : dataFromCamera(queue), conditionVar(condition) {}

grpc::Status ServerListeningManager::SendCameraData(grpc::ServerContext* context, const services::CameraDataRequest* request, services::CameraDataResponse* response) {
    FrameWrap frameWrap;
    frameWrap.frameNumber = request->framenumber();
    frameWrap.timestamp = request->timestamp();

    const std::string& imageDataString = request->image();
    std::vector<uint8_t> imageData(imageDataString.begin(), imageDataString.end());
    frameWrap.image = cv::imdecode(imageData, IMREAD_COLOR);

    dataFromCamera.push(frameWrap);
    conditionVar.notify_one();

    response->set_acknowledgment("Successfully.");
    return grpc::Status::OK;
}

void ServerListeningManager::startListen() {
    ConfigurationManager& configManager = ConfigurationManager::getInstance(); // Use reference to the singleton instance
    std::string serverIP = configManager.getFieldValue<std::string>("cameraIP");
    std::string serverPort = configManager.getFieldValue<std::string>("cameraPort");
    std::string server_address = serverIP + ":" + serverPort;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(this);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}
