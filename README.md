
# MobileyeBootcamp_ABUS


## open the folder MobileyeBootcamp_ABUS 
## click on the right button and open with visual studio and run
### need to add to PATH the locations of openCV/Build

### need to add to PATH in Envairoment system the loction of openCV/Build

#how to install wsl2


wsl --list --online
wsl --install -d Ubuntu -20.04
wsl --list --verbose
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

#Install WSL 2 Linux Kernel Update Package:
#Download the latest Linux kernel update package from: https://aka.ms/wsl2kernel
#Install the package you downloaded.

wsl --set-default-version 2
wsl

#how to install cmake in wsl2
sudo apt update
sudo apt install cmake
cmake --version

#how to run it in linux
sudo apt update
sudo apt install g++

#OpenCV uses CMake build configuration :
##sudo apt install build-essential cmake libopencv-dev
sudo apt install libopencv-dev

#start build:
mkdir -p build && cd build
rm -rf *
cmake ..
make
./ClientMain
#########

sudo make install
make -j4


#OpenCV uses CMake build configuration :
sudo apt install -y make
sudo apt install -y git
git clone https://github.com/opencv/opencv.git
git -C opencv checkout 4.x
#cmake ../opencv
export CXX=g++


###  docker
docker build -f docker/grpc.Dockerfile --build-arg GRPC_VERSION=1.34.0 --build-arg NUM_JOBS=8 --tag grpc-cmake:1.34.0 .

docker run -it --rm --network host -v $(pwd):/mnt grpc-cmake:1.34.0

### Build Examples

```bash
cmake -B build && cmake -B build && cmake --build build --config Release --parallel
cd  build
./ClientMain





