#include <zmq.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "fstream"
#include "iostream"
int main()
{
    zmq::context_t context(1);
    zmq::socket_t sock(context, ZMQ_REQ);
    sock.connect("tcp://localhost:6666");
    std::string data;
    {
        cv::Mat Imgdata = cv::imread("/home/lp74/Pictures/lena.jpg", cv::IMREAD_GRAYSCALE);
        std::vector<uchar> data_encode;
        cv::imencode(".jpg", Imgdata, data_encode);
        data = std::string(data_encode.begin(), data_encode.end());
        std::cout << "data:" << data;
    }
    // send
    {
        zmq::message_t message(data.size());
        memcpy(message.data(), data.c_str(), data.size());
        sock.send(message);
        zmq::message_t reply;
        socket.recv (&reply);
    }
    sock.close();
    system("pause");
    return 0;
}

/*
g++ -I/home/lp74/opencv/opencv-4.0.0/include/ -I/home/lp74/opencv/opencv-4.0.0/release/  -I/usr/local/include/opencv4/ zmq-client.cpp  -lzmq -lstdc++ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -o zmq-client
*/
