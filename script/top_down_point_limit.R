
ts_cal_vd <- function(x1, x2, x3, y1, y2, y3) {
  cy = 0
  cy = y1 + (y2 - y1) * (x3 - x1) / (x2 - x1);
  abs(cy - y3);
}

ts_top_down_point_limit <- function(seq, left, right, max_point) {
  
  res = matrix(nrow=2, ncol=max_point)
  
  res[1,1] = left
  res[1,2] = right
  res[2,1] = seq[left]
  res[2,2] = seq[right]
  
  num = 3
 
  while(num <= max_point) {
    temp = 0
    mini = 0
    for(j in seq(from=2, to=num-1, by=1)) {
      for(i in seq(from=res[1,j-1], to=res[1,j], by=1)) {
        err = ts_cal_vd(res[1,j-1], res[1,j], i, seq[res[1,j-1]], seq[res[1,j]], seq[i])
      #  print(err)
        if(err > temp) {
          temp = err
          mini = i
        }
      }
    }
    res[1,num] = mini
    res[2,num] = seq[mini]
    res = res[,order(res[1,], na.last=TRUE)]
    #print(res)
    num = num + 1
  }
  t(res)
  #ts_plott(res), seq)
}

ts_read_data <- function() {
  origin = c('../data/SandP_price.raw')
  segment = c('../data/SandP_big_m_chart.sample')
  
  read.table(file=origin, check.names=F) -> raw
  read.table(file=segment, check.names=F) -> data
  y1 = raw$V1
}

ts_plot <- function(data, time_series) {
  
    x1 = seq(from=1, to=nrow(time_series), by=1)
  
    x2 = as.vector(data[,1])
    y2 = as.vector(data[,2])
    
   # jpeg(paste("../data/pics/plot-", i, ".jpg", sep=""), width=1024, height=768, quality=100)

    ts.plot(y1[min(x2):max(x2)], lwd=2, col="blue", main="Top Down")
    lines(x1[x2-min(x2)+1], y1[x2], col="red")
}
