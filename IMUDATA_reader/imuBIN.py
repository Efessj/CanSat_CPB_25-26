import struct

HEADER = 0xAABBCCDD
SAMPLE_FMT = "<6hI"
SAMPLE_SIZE = struct.calcsize(SAMPLE_FMT)
BLOCK_SAMPLES = 200

BLOCK_SIZE = 4 + (SAMPLE_SIZE * BLOCK_SAMPLES)

buffer = b""

ACCEL_SCALE = 16384.0
GYRO_SCALE = 131.0



def read_imu_data(filename : str) -> list:
    data = []
    with open(filename, "rb") as f:
        while True:
            chunk = f.read(1024)
            if not chunk:
                break

            buffer += chunk

            while len(buffer) >= BLOCK_SIZE:
                header = struct.unpack_from("<I", buffer, 0)[0]

                if header == HEADER:
                    block = buffer[:BLOCK_SIZE]
                    buffer = buffer[BLOCK_SIZE:]


                    samples_data = block[4:]

                    for i in range(BLOCK_SAMPLES):
                        start = i * SAMPLE_SIZE
                        end = start + SAMPLE_SIZE

                        sample = struct.unpack(
                            SAMPLE_FMT,
                            samples_data[start:end]
                        )
                        data.append(sample)

                else:
                    buffer = buffer[1:]  # resincronizar

    return data

data = read_imu_data("imu_data.bin")

