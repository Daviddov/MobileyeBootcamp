#include "RectHandler.h"

//c'tor
RectHandler::RectHandler(FrameWrap& frameW, vector<Detection>& outputP, vector<string>& class_listP, SQLHandler &sqlHandler) :frameWarp(frameW), output(outputP), class_list(class_listP), sqlHandler(sqlHandler)
{
	colors = { Scalar(255, 255, 0),Scalar(0, 255, 0),Scalar(0, 255, 255),Scalar(255, 0, 0) };
}

void RectHandler::toDrawRect() {

	for (int i = 0; i < output.size(); ++i)
	{
		auto box = output[i].box;
		auto classId = output[i].class_id;
		const auto color = colors[classId % colors.size()];
		rectangle(frameWarp.image, box, color, 3);
		rectangle(frameWarp.image, Point(box.x, box.y - 5), Point(box.x + box.width, box.y), color, FILLED);
		putText(frameWarp.image, class_list[classId].c_str(), Point(box.x, box.y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));

		Logger::Info("origin frame width is %d"  " hight is %d ", frameWarp.image.cols , frameWarp.image.rows);
		Logger::Info("Top left x is %d Top left y is %d ", box.x, box.y);
		Logger::Info("Box width is %d Box hight is %d ", box.width, box.height);

		//Modify x and y for don't overflow from original frame.
		box.x < 0 ? box.x = 0 : box.x;
		box.y < 0 ? box.y = 0 : box.y;
		box.x > 20 ? box.x -= 20 : box.x;
		box.y > 20 ? box.y -= 20 : box.y;
		
		writeRectOnDB(box, class_list[classId]);
	}
}

void RectHandler::calcAvgPerChannel(const Mat& img, float* B, float* G, float* R) {

	float sumB = 0, sumG = 0, sumR = 0;
	for (int row = 0; row < img.rows; row++) {
		for (int col = 0; col < img.cols; col++) {
			const uchar* row_data = img.ptr(row);
			sumB += row_data[(col * 3) + 0];
			sumG += row_data[(col * 3) + 1];
			sumR += row_data[(col * 3) + 2];
		}
	}
	int size = img.rows * img.cols;
	*B = sumB / size;
	*G = sumG / size;
	*R = sumR / size;
}

void RectHandler::writeRectOnDB(Rect rect, string objectType) {

	Mat imgFromRect = frameWarp.image(rect);

	if (imgFromRect.empty()) {
		Logger::Error("Failed to extract rectangle from image.");
		return;
	}

	float R = 0, G = 0, B = 0;
	calcAvgPerChannel(imgFromRect, &R, &G, &B);


	if (sqlHandler.createTableIfNotExists()) {
			 sqlHandler.checkRectExistsInLastFrame(rect);
		if (sqlHandler.insertData(rect, frameWarp, objectType, R, G, B)) {
			//sqlHandler.selectMaxID();
			Logger::Info("write Rect On DB.");
		}
		else {
			Logger::Error("Failed to insert data.");
		}
	}
}



