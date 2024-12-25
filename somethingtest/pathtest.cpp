#include <stdio.h>  
#include <unistd.h> // 对于 getcwd  
#include <limits.h> // 对于 PATH_MAX  
#include <stdint.h>
#include <cstring>

#include <iostream>  
#include <bitset> 
struct VehicleInfo
{
	uint8_t turnSignal;
	uint8_t  DSeatUser;
};

struct GstMMinfo
{
    /* data */
    uint16_t chessInformation;
};

int main()
{
    VehicleInfo VehicleInfo_test{1,2};
    GstMMinfo MmInfo{};
    std::bitset<16> binary(MmInfo.chessInformation);

    memcpy(&MmInfo.chessInformation,&VehicleInfo_test.DSeatUser,1);

    MmInfo.chessInformation = MmInfo.chessInformation & 0x0007U;
    MmInfo.chessInformation =
        static_cast<uint16_t>(MmInfo.chessInformation << 2);
    
    std::bitset<16> binary_1(MmInfo.chessInformation);
    std::cout << "整数: " << MmInfo.chessInformation << std::endl;  
    std::cout << "二进制: " << binary_1 << std::endl;  

    uint16_t chessInformation{0U};
    chessInformation = VehicleInfo_test.turnSignal;

    std::bitset<16> binary_3(chessInformation);
    std::cout << "整数: " << chessInformation << std::endl;  
    std::cout << "二进制: " << binary_3 << std::endl; 



    chessInformation = chessInformation & 0x0003U;
    MmInfo.chessInformation |= chessInformation;

    MmInfo.chessInformation = MmInfo.chessInformation << 2;

    std::bitset<16> binary_2(MmInfo.chessInformation);
    std::cout << "整数: " << MmInfo.chessInformation << std::endl;  
    std::cout << "二进制: " << binary_2 << std::endl; 

    return 0;
}