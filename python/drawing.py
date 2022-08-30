from cProfile import label
import os
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

path_to_file = os.path.join(os.path.dirname(__file__), "../")
with open(path_to_file + 'dataset/wheel1.txt', "r") as file1:
    velocity = [float(i) for line in file1 for i in line.split(',') if i.strip()]
with open(path_to_file + "results/result_velocity.txt", "r") as file3:
    draw_fvelocity = [float(i) for line in file3 for i in line.split(',') if i.strip()]

time_plot = [t*0.1 for t in range(0, len(draw_fvelocity))]

i = 0
different_velocity = []
while i < len(velocity):
    different_velocity.append(abs(velocity[i] - draw_fvelocity[i]))
    i+=1

fig1 = plt.figure(constrained_layout=True)
fig1_gs = gridspec.GridSpec(ncols=1, nrows=1, figure=fig1)

fig1_ax1 = fig1.add_subplot(fig1_gs[0,0],title='Velocity')
fig1_ax1.grid(True)

fig1_ax1.set_xlabel('Time (sec)')
fig1_ax1.set_ylabel('Velocity')

fig1_ax1.plot(time_plot, velocity,'#1f77b4', label="measured speed")
fig1_ax1.plot(time_plot, draw_fvelocity, '#ff7f0e', label="estimated speed")
fig1_ax1.plot(time_plot, different_velocity, 'blue')

plt.legend(loc="upper left")
plt.ylim(0.0, 200.0)
plt.show()