import bar_chart

if __name__ == "__main__":


  figure_folder='./'

  # draw bar chart
  x_values = ['Amazon','YouTube']

  y_values = []
  y_values.append([446,52.8])
  y_values.append([499,65.2])
  y_values.append([548,86.3])
  y_values.append([507,63.8])

  legend_labels = ['Skip-list', 'cdf-list', 'bound-list', 'partition-list']

  bar_chart.DrawFigure(x_values, y_values, legend_labels, 'dataset', 'QPS [W/s]', 0, 30, figure_folder, 'real-set', True)

