import bar_chart

if __name__ == "__main__":


  figure_folder='./'

  # draw bar chart
  x_values = ['Amazon','YouTube']

  y_values = []
  y_values.append([1,1])
  y_values.append([1.12,1.23])
  y_values.append([1.23,1.63])
  y_values.append([1.14,1.21])

  legend_labels = ['Skip-list', 'cdf-list', 'bound-list', 'partition-list']

  bar_chart.DrawFigure(x_values, y_values, legend_labels, 'dataset', 'speedup', 0, 2, figure_folder, 'real-set-speedup', True)

