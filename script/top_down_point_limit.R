
ts_cal_vd <- function(x1, x2, x3, y1, y2, y3) {
  cy = 0
  cy = y1 + (y2 - y1) * (x3 - x1) / (x2 - x1);
  abs(cy - y3);
}

ts_top_down_point_limit <- function(seq, left, right, max_point) {
  res = matrix(nrow=2, ncol=2)
  
  res[1,1] = left
  res[1,2] = right
  res[2,1] = seq[left]
  res[2,2] = seq[right]
  
  while(ncol(res) <= max_point) {
    temp = 0
    mini = 0
    for(j in seq(from=2, to=ncol(res), by=1)) {
      for(i in seq(from=res[1,j-1], to=res[1,j], by=1)) {
        err = ts_cal_vd(res[1,j-1], res[1,j], i, seq[res[1,j-1]], seq[res[1,j]], seq[i])
        #  print(err)
        if(err > temp) {
          temp = err
          mini = i
        }
      }
    }
    res = cbind(res, c(mini, seq[mini]))
    res = res[,order(res[1,], na.last=TRUE)]
    #print(res)
  }
  t(res)
  #ts_plott(res), seq)
  
}

ts_pip_detect_error_limit <- function(seq, left, right, max_err) {
  
  res = matrix(nrow=2, ncol=2)
  
  res[1,1] = left
  res[1,2] = right
  res[2,1] = seq[left]
  res[2,2] = seq[right]
 
  while(ncol(res) <= right-left+1) {
    temp = 0
    mini = 0
    pindx = 0
    for(j in seq(from=2, to=ncol(res), by=1)) {
      for(i in seq(from=res[1,j-1], to=res[1,j], by=1)) {
        err = ts_cal_vd(res[1,j-1], res[1,j], i, seq[res[1,j-1]], seq[res[1,j]], seq[i])
       # print(temp)
        if(err > temp) {
          temp = err
          mini = i
          pindx = j-1
        }
      }
    }
    if(mini == 0) {
      break
    }
    
    if(temp / abs(res[2,pindx] - res[2,pindx+1]) < max_err) {
      
      break
    }
      res <- cbind(res, c(mini, seq[mini]))
      res = res[,order(res[1,], na.last=TRUE)]
    #  print(res)
  }
  t(res)
  #ts_plott(res), seq)
}

ts_read_data <- function() {
  origin = c('../data/SandP_price.raw')
  
  read.table(file=origin, check.names=F) -> raw
  matrix(raw$V1)
}

ts_run <- function() {
  raw = ts_read_data();
  ts_pip_detect_error_limit(raw[,1], 10000, nrow(raw), 0.1) -> pip
  
  ts_up_trend(pip) -> pup
  ts_down_trend(pips) -> pdown
  
  ts_plot(pup, raw)
}

ts_plot <- function(data, time_series) {
  
    x1 = seq(from=1, to=nrow(time_series), by=1)
  
    x2 = as.vector(data[,1])
    y2 = as.vector(data[,2])
    
   # jpeg(paste("../data/pics/plot-", i, ".jpg", sep=""), width=1024, height=768, quality=100)

    ts.plot(time_series[min(x2):max(x2),1], lwd=2, col="blue", main="Top Down")
    lines(x1[x2-min(x2)+1], y1[x2], col="red")
}

ts_up_trend <- function(pips) {
  rate = 0.05
  pips[pips[2:nrow(pips),2] - pips[1:nrow(pips)-1, 2] > pips[1:nrow(pips)-1, 2] * rate, ]
}

ts_down_trend <- function(pips) {
  rate = 0.05
  pips[pips[2:nrow(pips),2] - pips[1:nrow(pips)-1, 2] < -pips[1:nrow(pips)-1, 2] * rate, ]
}
