import matplotlib.pyplot as plt

seg_size = [2, 4, 8, 16, 32]

ticks = [465470703000, 411529463000, 337732260000, 349995128000, 450206797000]

plt.figure(figsize=(8, 6))

plt.bar(seg_size, ticks, color='skyblue')

plt.title('Gem5 metrics of all segments for 64-bit BFS')

plt.xlabel('segment size')
plt.ylabel('time')

plt.xticks(seg_size, [str(2**i) for i in range(1, len(seg_size)+1)])
plt.grid(True)
plt.show()