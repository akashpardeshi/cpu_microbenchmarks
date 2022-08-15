import matplotlib.pyplot as plt

def plot(x_data, y_data, x_scale, y_scale, title, x_label, y_label):
    plt.plot(x_data, y_data, '.-')
    plt.xscale(x_scale)
    plt.xscale('log', base=2) if x_scale == 'log' else plt.xscale(x_scale)
    plt.yscale('log', base=2) if y_scale == 'log' else plt.yscale(y_scale)

    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)

    plt.show()

def read_input():
    title, x_scale, y_scale = [input().split(': ')[1] for _ in range(3)]

    x_label, y_label = None, None
    x_data, y_data = [], []
    while True:
        try:
            line = input()
            if not x_label:
                x_label = line.split(', ')[0].split(': ')[0]
            if not y_label:
                y_label = line.split(', ')[1].split(': ')[0]
            x_data.append(int(line.split(', ')[0].split(': ')[1]))
            y_data.append(float(line.split(', ')[1].split(': ')[1]))
        except EOFError:
            break

    plot(x_data, y_data, x_scale, y_scale, title, x_label, y_label)

read_input()
