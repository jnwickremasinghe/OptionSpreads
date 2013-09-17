setwd("C:/Users/ub70064/Documents/workspace/Quotes")
quotes <- read.csv("quotes.csv")

index=which (quotes$type=='last')
last=quotes[index,]


FB=last[last$symbol=='FB',]
ORCL=last[last$symbol=='ORCL',]

FB<-FB[-which(FB$value<20),]



FB<-FB[-531,]

plot(FB$value)
plot(ORCL$value)

ORCL<-ORCL[-which(ORCL$value>33),]

library(DBI)
library(RSQLite)
library(strucchange)
drv<-dbDriver("SQLite")
setwd("C:/Users/ub70064/Documents/workspace/Quotes")
con<-dbConnect(drv,dbname="test.db")
con<-dbConnect(drv,dbname="quotes.db")
res<-dbSendQuery(con,"select *, date ||' '|| time as date_time from quote where symbol='FB' and type='last' and value<40 and value>33 and date='2013-07-29';" )
data<-fetch(res,n=90000)
dbClearResult(res)

#need timezone
data$date_time<-as.POSIXct(data$date_time,format="%Y-%m-%d %H:%M:%S")
pct=c(0,(data$value[-1]-data$value[-nrow(data)])/data$value[-nrow(data)])
data$pct<-pct*100

#which(abs(data$pct)>.1)
plot(data$date_time,data$value)

xrange=range(data$date_time)
yrange=range(data$value)

plot(xrange, yrange, type="o", xlab="Time",
		ylab="Price ($)" )
plot(data$date_time,data$value,type=)
axis.POSIXct(1,data$date_time)

sample_size=50
num_samples=floor(length(data$pct)/sample_size)
ranges = matrix(0,num_samples,2)

for (sample_num in 1:num_samples )	{
	sample_filter=1:((sample_size)*sample_num)
	sample=data[sample_filter,]
	sample_mean=mean(sample$pct)
	sample_sd=sd(sample$pct)
	sample$deviation<-sample$pct-sample_mean
	sample$running_sum<-cumsum(sample$deviation);
	R=range(sample$running_sum)[2]-range(sample$running_sum)[1]
	rescaled_range=R/sample_sd
	ranges[sample_num,1]=log(length(sample$pct)) #n
	ranges[sample_num,2]=log(rescaled_range) # R/s
}

rescaled<-data.frame(ranges)
colnames(rescaled)<-c("X","Y")

sample=rescaled[1:100,];

fitted<-lm(sample$Y~sample$X)
me.mefp<-mefp(as.formula(fitted),type="ME",data=sample, alpha=0.05)

sample=rescaled[1:200,]
me.mefp<-monitor(me.mefp)

sample=rescaled[1:300,]
me.mefp<-monitor(me.mefp)

plot(ranges[,1],ranges[,2])
plot(ranges[300:500,1],ranges[300:500,2])




#strucchange

data("USIncExp")
USIncExp2 <- window(USIncExp, start = c(1985,12))

coint.res <- residuals(lm(expenditure ~ income, data = USIncExp2))
coint.res <- lag(ts(coint.res, start = c(1985,12), freq = 12), k = -1)
USIncExp2 <- cbind(USIncExp2, diff(USIncExp2), coint.res)
USIncExp2 <- window(USIncExp2, start = c(1986,1), end = c(2001,2))
colnames(USIncExp2) <- c("income", "expenditure", "diff.income", "diff.expenditure", "coint.res")
ecm.model <- diff.expenditure ~ coint.res + diff.income

USIncExp3 <- window(USIncExp2, start = c(1986, 1), end = c(1989,12))
me.mefp <- mefp(ecm.model, type = "ME", data = USIncExp3, alpha = 0.05)


USIncExp3 <- window(USIncExp2, start = c(1986, 1), end = c(1990,12))

me.mefp <- monitor(me.mefp)

USIncExp3 <- window(USIncExp2, start = c(1986, 1))

me.mefp <- monitor(me.mefp)
me.mefp



# Create Line Chart

# convert factor to numeric for convenience 
Orange$Tree <- as.numeric(Orange$Tree) 
ntrees <- max(Orange$Tree)

# get the range for the x and y axis 
xrange <- range(Orange$age) 
yrange <- range(Orange$circumference) 
axis.Posixct(1,)
# set up the plot 

colors <- rainbow(ntrees) 
linetype <- c(1:ntrees) 
plotchar <- seq(18,18+ntrees,1)

# add lines 
for (i in 1:ntrees) { 
	tree <- subset(Orange, Tree==i) 
	lines(tree$age, tree$circumference, type="b", lwd=1.5,
			lty=linetype[i], col=colors[i], pch=plotchar[i]) 
} 

# add a title and subtitle 
title("Tree Growth", "example of line plot")

# add a legend 
legend(xrange[1], yrange[2], 1:ntrees, cex=0.8, col=colors,
		pch=plotchar, lty=linetype, title="Tree")

