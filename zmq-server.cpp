#include <zmq.hpp>
#include <string.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "fstream"
#include "iostream"

int main()
{
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:6666");
    while (true)
    {
        //  receive message
        std::string msgStr;
        {
            zmq::message_t message;
            if(socket.recv(&message)){
                
                zmq::message_t reply (5);
                memcpy (reply.data (), "World", 5);
                msgStr = std::string((char*)message.data(), message.size());
                //  unserialize to cv::mat
                cv::Mat loaded_data;
                {
                    std::vector<uchar> data(msgStr.begin(), msgStr.end());
                    loaded_data = cv::imdecode(data, cv::IMREAD_GRAYSCALE);
                    socket.send (reply);
                }
                //  show cv::mat
                /*
                {
                    std::cout << "waiting for your key press on the image." << "\n";
                    cv::imshow("load", loaded_data);
                    cv::waitKey(0);
                }
                */
            };            
        }
    }
    socket.close();
    return 0;
}

/*
g++ -I/home/lp74/opencv/opencv-4.0.0/include/ -I/home/lp74/opencv/opencv-4.0.0/release/  -I/usr/local/include/opencv4/ zmq-server.cpp  -lzmq -lstdc++ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -o zmq-server
*/
