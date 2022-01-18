#  getting a big number,  > 16 bits

# need 0xF7F0_0A0C

lui $s0, 0xF7F0       #   put first 16 bits in

ori $s0, $s0, 0x0A0C   # this will OR the bottom half of 16 zeros, loading the big number