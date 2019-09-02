# Sending cv2 images from client to server (and back)

## Refs
[stackoverflow](https://stackoverflow.com/questions/55619871/how-to-i-transfer-an-imageopencv-matrix-numpy-array-from-c-publisher-to-pyth)

##TODO
Either reply to the REQ socket after receiving the first image or use another pattern : ZMQ_PAIR, PUSH / PULL, ROUTER / DEALER could all work in your case. Read the documentation to learn about the different pattern.

Also, you don't have to convert your image in a string. You can directly send std::vector<uint8_t>using zmq : you can access the underlying pointer using std::vector::data() and memcpy(message.data(), vector.data(), vector.size()
