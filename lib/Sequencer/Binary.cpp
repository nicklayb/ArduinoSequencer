#include <Binary.h>

int inputByteToMultiplexerBits(int byte, int byteLength)
{
  int checkByte = 0b1;
  for (int i = 1; i <= byteLength; i++)
  {
    if ((byte & checkByte) > 0)
    {
      return i;
    }
    checkByte = checkByte << 1;
  }
  return 0;
}
