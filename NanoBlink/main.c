int main(void)
{
  *(unsigned int*)(0x40021034) = 1U; // Enable only GPIOA clock in the RCC IOPENR register
  *(unsigned int*)(0x50000000) = (1U << 24); // Set only PA12 as push/pull output in the GPIOA MODER register

  while (1) // Main loop
  {
    for (volatile unsigned int n = 500000; n > 0; n--); // Delay loop
    *(unsigned int*)(0x50000014) ^= (1U << 12); // Toggle PA12 in the GPIOA ODR register
  }
}

extern unsigned long _estack; // Import stack pointer address from linker file
__attribute__ ((section(".isr_vector"))) // Setup memory placement in flash for the vector table

void* vector_table[] = // Minimized vector table
{
  (void*)(&_estack), // Stack Pointer
  (void*)&main // Reset vector
};
