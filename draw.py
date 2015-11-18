import numpy as np
import matplotlib.pyplot as plt
import sys


def plot_density_map(points_file, density_file):
    M = np.loadtxt(points_file, skiprows=1)
    bins_x = 600
    bins_y = 600
    H, xedges, yedges = np.histogram2d(M[:,0], M[:,1], [bins_x, bins_y])
    X, Y = np.meshgrid((xedges[1:] + xedges[:-1]) / 2,
                       (yedges[1:] + yedges[:-1]) / 2)
    plt.contourf(X, Y, H, cmap='jet')
    plt.title('Density map')
    plt.xlabel('X')
    plt.ylabel('Y')
    fig = plt.gcf()
    fig.set_size_inches(13.66, 7.68)
    fig.savefig(density_file, dpi=200)
    plt.clf()


def plot_trajectories(paths_file, traj_file):
    paths_to_plot = [[[],[]],[[],[]],[[],[]],[[],[]]]
    with open(paths_file, 'r') as paths_f:
        i = 0
        for line in paths_f:
            if line != '========\n' and line != '':
                parsed = list(map(float, line.split(' ')))
                paths_to_plot[i][0].append(parsed[0])
                paths_to_plot[i][1].append(parsed[1])
            else:
                i += 1
    plt.title('Trajectories')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.plot(paths_to_plot[0][0], paths_to_plot[0][1], color='red')
    plt.plot(paths_to_plot[1][0], paths_to_plot[1][1], color='green')
    plt.plot(paths_to_plot[2][0], paths_to_plot[2][1], color='blue')
    plt.plot(paths_to_plot[3][0], paths_to_plot[3][1], color='yellow')
    fig = plt.gcf()
    fig.set_size_inches(13.66, 7.68)
    fig.savefig(traj_file, dpi=200)
    plt.clf()


def main(args):
    points = args[0]
    paths = args[1]
    plot_density_map(points, 'density.png')
    plot_trajectories(paths, 'trajectories.png')
    print('Done')


if __name__ == '__main__':
    main(sys.argv[1:])
