import wave
import struct

f = wave.open('out.wav', 'w')

sampleRate = 22000
frequency = 440.0
duration = 0.2

f.setnchannels(1)
f.setsampwidth(2)
f.setframerate(sampleRate)

msg_str = 'vaibhav handwash'
msg = []

def transform_msg():
    for i in msg_str:
        t = oct(ord(i))[2:]
        for j in t:
            msg.append(int(j))

transform_msg()

print(msg_str)
print(msg)

msg.append(6)

unit = 3800
last_value = 0
amplitude = [-32000, -24000, -16200, -8100, 8100, 16200, 24000, 32000]

for j in msg:
    for i in range(int(sampleRate * duration)):
        value = amplitude[j]
        last_value = j
        data = struct.pack('<h', value)
        f.writeframesraw(data)

a = amplitude[last_value] / int(sampleRate * duration)

for i in range(int(sampleRate * duration),1,-1):
    value = int(a*i)
    if type(value) is not int:
        print("value XX ")
        print(value)
        print(type(value))
        input()
    data = struct.pack('<h', value)
    f.writeframesraw(data)

f.writeframes(''.encode())
f.close()
