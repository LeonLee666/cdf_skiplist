from common import *

# example for reading csv file
def ReadFile():
  parameters = []
  standards = []
  cdfs = []
  bounds = []
  partitions = []
  with open('hot-zipf.csv') as csvfile:
    rows = csv.reader(csvfile, delimiter = ',')
    
    count = 0
    for row in rows:
      parameters.append(float(row[0]))
      standards.append(float(row[1]))
      cdfs.append(float(row[2])) 
      bounds.append(float(row[3]))
      partitions.append(float(row[4]))

  lines = [standards, cdfs, bounds, partitions]
  return parameters, lines

# draw a line chart
def DrawFigure(x_values, y_values, legend_labels, x_label, y_label, x_min, x_max, y_min, y_max, folder, filename, allow_legend, color_map = COLOR_MAP):

  assert(len(legend_labels) >= len(y_values))

  # you may change the figure size on your own.
  fig = plt.figure(figsize=(5,3.5))
  ax = fig.add_subplot(111)

  lines = [None] * (len(y_values))
  for i in range(len(y_values)):
    lines[i], = ax.plot(x_values, y_values[i], color=color_map[i], \
                linewidth=LINE_WIDTH, marker=MARKERS[i], \
                markersize=MARKER_SIZE, label=legend_labels[i])

  # sometimes you may not want to draw legends.
  if allow_legend == True:
    ax.legend(lines, legend_labels, prop=LEGEND_FP, 
                     loc='upper center', ncol=2, bbox_to_anchor=(0.45, 1.2), shadow=False,
                     frameon=False, borderaxespad=0.0, handlelength=2, labelspacing=0.2)

  plt.xticks(x_values)
  # you may control the limits on your own.
  plt.xlim(x_min, x_max)
  plt.ylim(y_min, y_max)

  ax.grid(axis='y',color='gray')
  #ax.set_xscale('log',basex=2)
  ax.yaxis.set_major_locator(LinearLocator(6))
  ax.xaxis.set_major_locator(LinearLocator(6))
  
  ax.get_xaxis().set_tick_params(direction='in', pad=10)
  ax.get_yaxis().set_tick_params(direction='in', pad=10)
  
  plt.xlabel(x_label, fontproperties=LABEL_FP)
  plt.ylabel(y_label, fontproperties=LABEL_FP)
  
  size = fig.get_size_inches()
  dpi = fig.get_dpi()

  if not os.path.exists(folder):
    os.makedirs(folder)
  
  plt.savefig(folder + "/" + filename + ".svg", bbox_inches='tight', format='svg')


if __name__ == "__main__":

  figure_folder='./'

  # draw line chart
  legend_labels = ['Skip-list', 'partition-list', 'hot-list', 'mix-list']
  parameters, lines = ReadFile()

  DrawFigure(parameters, lines, legend_labels, 'Parameters', 'QPS [W/s]', 0, 0.8
, 0, 100, figure_folder, 'hot-zipf', True)


