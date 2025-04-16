#ifndef IMAGEWORKER_H
#define IMAGEWORKER_H

#include <string>
#include <vector>
#include <cstdint>

class ImageWorker
{
public:
    explicit ImageWorker();
    ~ImageWorker();

    std::string base64_encode(const std::vector<uint8_t>& buffer);
    std::vector<uint8_t> base64_decode(const std::string& encoded_string);

private:

};

#endif // IMAGEWORKER_H
