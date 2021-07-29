#socat -d -d -v pty,rawer,echo=0,link=./reader pty,rawer,echo=0,link=./writer

import asyncio
import serial_asyncio


async def main(loop):
    #reader, _ = await serial_asyncio.open_serial_connection(url='/dev/pts/1', baudrate=115200)
    reader, _ = await serial_asyncio.open_serial_connection(url='/dev/ttyUSB0', baudrate=115200)
    print('Reader created')
    #received = recv(reader)
    taskRec = asyncio.create_task(recv(reader))
    await asyncio.wait({taskRec})


async def recv(r):
    while True:
        msg = await r.readuntil(b'\n')
        if msg.rstrip() == b'quit':
            print('Done receiving')
            break
        print(f'received: {msg.rstrip().decode()}')


loop = asyncio.get_event_loop()
loop.run_until_complete(main(loop))
loop.close()
