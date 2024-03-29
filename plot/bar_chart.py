from common import *

# draw a line chart
def DrawFigure(x_values, y_values, legend_labels, x_label, y_label, y_min, y_max, folder, filename, allow_legend, color_map = COLOR_MAP, patterns = PATTERNS):

  assert(len(legend_labels) >= len(y_values))
  
  # you may change the figure size on your own.
  fig = plt.figure(figsize=(5,4))
  figure = fig.add_subplot(111)

  # values in the x_xis
  index = np.array(range(1, len(x_values) + 1))
  # draw the bars
  bars = [None] * (len(y_values))

  if len(y_values) == 1:
    width = 0.4
    i = 0
    bars[i] = figure.bar(index, y_values[i], width, hatch=patterns[i], color=color_map[i], edgecolor="black", label=legend_labels[i])

  elif len(y_values) == 2:
    width = 0.3
    i = 0
    bars[i] = figure.bar(index - width / 2, y_values[i], width, hatch=patterns[i], color=color_map[i], edgecolor="black", label=legend_labels[i])
    i = 1
    bars[i] = figure.bar(index + width / 2, y_values[i], width, hatch=patterns[i], color=color_map[i], edgecolor="black", label=legend_labels[i])

  elif len(y_values) == 3:
    width = 0.2
    i = 0
    bars[i] = figure.bar(index - width, y_values[i], width, hatch=patterns[i], color=color_map[i], edgecolor="black", label=legend_labels[i])
    i = 1
    bars[i] = figure.bar(index, y_values[i], width, hatch=patterns[i], color=color_map[i], edgecolor="black", label=legend_labels[i])
    i = 2
    bars[i] = figure.bar(index + width, y_values[i], width, hatch=patterns[i], color=color_map[i], edgecolor="black", label=legend_labels[i])
  
  elif len(y_values) == 4:
    width = 0.2
    i = 0
    bars[i] = figure.bar(index - width, y_values[i], width, hatch=patterns[i], color=color_map[i], edgecolor="black", label=legend_labels[i])
    i = 1
    bars[i] = figure.bar(index, y_values[i], width, hatch=patterns[i], color=color_map[i], edgecolor="black", label=legend_labels[i])
    i = 2
    bars[i] = figure.bar(index + width, y_values[i], width, hatch=patterns[i], color=color_map[i], edgecolor="black", label=legend_labels[i])
    i = 3
    bars[i] = figure.bar(index + 2*width, y_values[i], width, hatch=patterns[i], color=color_map[i], edgecolor="black", label=legend_labels[i])

  else:
    assert(False)

  # sometimes you may not want to draw legends.
  if allow_legend == True:
    figure.legend(bars, legend_labels, prop=LEGEND_FP, 
                     loc='upper center', ncol=2, bbox_to_anchor=(0.45, 1.2), shadow=False,
                     frameon=False, borderaxespad=0.0, handlelength=2, labelspacing=0.2)

  plt.xticks(index, x_values)

  # plt.xlim(0,)
  # plt.ylim(y_min,y_max)

  figure.grid(axis='y',color='gray',linestyle='--')
  figure.yaxis.set_major_locator(LinearLocator(6))
  
  figure.get_xaxis().set_tick_params(direction='in', pad=10)
  figure.get_yaxis().set_tick_params(direction='in', pad=10)
  
  plt.xlabel(x_label, fontproperties=LABEL_FP)
  plt.ylabel(y_label, fontproperties=LABEL_FP)

  size = fig.get_size_inches()
  dpi = fig.get_dpi()
  
  if not os.path.exists(folder):
    os.makedirs(folder)

  plt.savefig(folder + "/" + filename + ".svg", bbox_inches='tight', format='svg')


def DrawLegend(legend_labels, folder, filename, color_map = COLOR_MAP, patterns = PATTERNS):
  fig = pylab.figure()
  ax1 = fig.add_subplot(111)
  LEGEND_FP = FontProperties(style='normal', size=26)

  bars = [None] * (len(legend_labels))
  data = [1]
  x_values = [1]

  for i in range(len(legend_labels)):
    bars[i] = ax1.bar(x_values, data, hatch=patterns[i], color=color_map[i], edgecolor="black", linewidth=0.2)

  # LEGEND
  figlegend = pylab.figure(figsize=(12, 0.5))
  figlegend.legend(bars, legend_labels, prop=LEGEND_FP, \
                   loc=1, ncol=len(legend_labels), mode="expand", shadow=False, \
                   frameon=False, borderaxespad=0.0, handlelength=2)

  if not os.path.exists(folder):
    os.makedirs(folder)

  figlegend.savefig(folder + '/' + filename + '.svg', bbox_inches='tight', format='svg')


