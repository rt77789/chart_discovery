###
###
###


plot_path <- function(origin, segment, ofile) {

	read.table(file=segment, check.names=F) -> seg_out
		read.table(file=origin, check.names=F) -> seg_input 

		x1 = seg_input$V1
		y1 = seg_input$V2

		x2 = seg_out$V1
		y2 = seg_out$V2

		jpeg(ofile, width=1024, height=768, quality=100)
		ts.plot(y1, lwd=2, col="blue", main="Random Walk")
		lines(x1[x2], y1[x2], col="red")
#seqplot.ts(x=x1, y=y1)
		dev.off()

#jpeg('seg_out.pdf')
#ts.plot(y2, lwd=2, col="blue", main="Random Walk")
#@dev.off()

}

origin = c('~/code/time_series_segment/random_ts.data.new')
segment = c( '~/code/time_series_segment/sliding_window.out', '~/code/time_series_segment/top_down.out' #'~/code/time_series_segment/bottom_up.out'
		)

ofiles = c('sliding_window.jpg', 'top_down.jpg')

plot_path(origin[1], segment[1], ofiles[1]);
plot_path(origin[1], segment[2], ofiles[2]);

