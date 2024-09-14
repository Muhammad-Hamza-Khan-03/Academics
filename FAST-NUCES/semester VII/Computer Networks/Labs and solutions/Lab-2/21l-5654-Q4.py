import sys
import struct


number = 0x3412

byte_order = sys.byteorder

if byte_order == 'little':
	byte_representation = struct.pack('<H', number)
else:
	struct.pack('>H', number)

if byte_order == 'little':
	print("Byte Order: Little Endian")
else:
	print("Byte Order: Big Endian")	

for b in byte_representation:
	print("Stored Bytes", ' '.join(f'0x{b:02x}'))
	
