###
###
###

origin = c('../data/SandP_price.raw')
segment = c('../data/SandP_big_m_chart.sample')

read.table(file=origin, check.names=F) -> time_series
read.table(file=segment, check.names=F) -> data

x1 = seq(from=1, to=nrow(time_series), by=1)
	y1 = time_series$V1

	for(i in 1:nrow(data)) {
		x2 = as.vector(t(data[i,seq(from=3, to=16, by=2)]))
			y2 = as.vector(t(data[i,seq(from=4, to=16, by=2)]))
			x2 = x2 + 1

			jpeg(paste("../data/pics/plot-", i, ".jpg", sep=""), width=1024, height=768, quality=100)
#ts.plot(y1, lwd=2, col="blue", main="Random Walk")

#lines(x1[x2], y1[x2], col="red")
			ts.plot(y1[min(x2):max(x2)], lwd=2, col="blue", main=paste("Sim=", data[i,1], ", Err=", data[i,2], sep=""))
							   lines(x1[x2-min(x2)+1], y1[x2], col="red")
#seqplot.ts(x=x1, y=y1)
										   dev.off()
	}
#jpeg('seg_out.pdf')
#ts.plot(y2, lwd=2, col="blue", main="Random Walk")
#@dev.off()


