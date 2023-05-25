#include <iostream>
#include <cstdint>

void RGBC_Read(uint16_t* buffer)
{
	buffer[0] = 10;
    buffer[1] = 20;
    buffer[2] = 30;
    buffer[3] = 40;
}

int main() {
    uint16_t RGBC_Buffer[4] = {0, 0, 0, 0};

    std::cout << "Before modification: ";
    for (const auto& element : RGBC_Buffer) {
        std::cout << element << " ";
    }

    RGBC_Read(RGBC_Buffer);

    std::cout << "\nAfter modification: ";
    for (const auto& element : RGBC_Buffer) {
        std::cout << element << " ";
    }

    return 0;
}

