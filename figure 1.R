# set up

## load packages and model
source("~/Documents/GitHub/covid_vaccines_virulence_evolution/functions.R")

library(deSolve)
library(rootSolve)
library(viridis)

system("R CMD SHLIB epi.model.c")
dyn.load(paste("~/Documents/GitHub/covid_vaccines_virulence_evolution/epi.model", .Platform$dynlib.ext, sep = ""))

## define model parameters

gamma<-1/7

rU<-.0 #vaccinated class
rL<-0 #vaccinated class
rUc<-0 #convalescent class
rLc<-0 #convalescent class

A<-c(seq(.0025,.2,.00025))
res<-11
rUv.steps<-rLv.steps<-seq(.5,1,length.out = res)

omega<-0
omegav<-0

gamma<-1/7
q=1/10
epsilon<-.5
p<-50


# generate plot data 

# saturating trade-off
optim.alpha.assumed<-.01 #set to either .00875, .01, .02
alpha.obs<-.01
R0.assumed<-5.625

rUv<-0 #vaccinated class
rLv<-0 #vaccinated class
rUc<-0 #convalescent class
rLc<-0 #convalescent class
rUcv<-0 #vaccinated + convalescent class
rLcv<-0 #vaccinated + convalescent class

get.states(0,0,0)
b2<-uniroot(b2.search,c(0,1),b1=1,optim.alpha.assumed=optim.alpha.assumed,tol=1e-15)$root
b1<-uniroot(R0.search,c(0,200),alpha=optim.alpha.assumed,b2=b2,tol=1e-10)$root

trans.rates1<-b1*(A-.0025)^b2
death.rates1<-1/(A*p+gamma)
out<-find.optim.vir(A,b1,b2,rU,rL,0,0)
R0s1<-out[[2]]

# non-saturating trade-off
optim.alpha.assumed<-.01 #set to either .00875, .01, .02
alpha.obs<-.01
R0.assumed<-5.625

rUv<-0 #vaccinated class
rLv<-0 #vaccinated class
rUc<-0 #convalescent class
rLc<-0 #convalescent class
rUcv<-0 #vaccinated + convalescent class
rLcv<-0 #vaccinated + convalescent class

get.states(0,0,0)
b2<-1
b1<-300

trans.rates2<-b1*(A-.0025)^b2
death.rates2<-1/(A*p+gamma)
out<-find.optim.vir(A,b1,b2,rU,rL,0,0)
R0s2<-out[[2]]

# no trade-off
optim.alpha.assumed<-.01 #set to either .00875, .01, .02
alpha.obs<-.01
R0.assumed<-5.625

rUv<-0 #vaccinated class
rLv<-0 #vaccinated class
rUc<-0 #convalescent class
rLc<-0 #convalescent class
rUcv<-0 #vaccinated + convalescent class
rLcv<-0 #vaccinated + convalescent class

get.states(0,0,0)
b2<-uniroot(b2.search,c(0,1),b1=1,optim.alpha.assumed=optim.alpha.assumed,tol=1e-15)$root
b1<-uniroot(R0.search,c(0,200),alpha=optim.alpha.assumed,b2=b2,tol=1e-10)$root

trans.rates3<-b1*(A-.0025)^b2
death.rates3<-rep(1/gamma,time=length(A))
out<-find.optim.vir(A,2*b1,b2,rU,1,0,1) #double transmission to account for loss of transmission from lRt
R0s3<-out[[2]]


# plot

par(mfrow=c(1,3),mar=c(5,5,4,1))
plot(A,trans.rates1,xlim=c(0.0025,.021),ylim=c(0,6),xlab="virulence",ylab="transmisison rate",type="n",cex.lab=2,cex.axis=1.2)
points(A,trans.rates1,col=viridis(3)[1],type="l",lwd=12,lty=1)
points(A,trans.rates2,col=viridis(3)[2],type="l",lwd=12,lty=1)
points(A,trans.rates3,col=viridis(3)[3],type="l",lwd=12,lty=2)
mtext("A",side=3,line=1,font=2,adj=0,padj = 0)

#par(fig = c(1/3,2/3, 0, 1), new = T)
plot(A,death.rates1,xlim=c(.0025,.021),ylim=c(0,7),xlab="virulence",ylab="transmisison time",type="n",cex.lab=2,cex.axis=1.2)
points(A,death.rates1,col=viridis(3)[1],type="l",lwd=12,lty=1)
points(A,death.rates2,col=viridis(3)[2],type="l",lwd=12,lty=2)
points(A,death.rates3,col=viridis(3)[3],type="l",lwd=12,lty=1)
mtext("B",side=3,line=1,font=2,adj=0,padj = 0)

#par(fig = c(2/3,3/3, 0, 1), new = T)
plot(A,R0s1,xlim=c(.0025,.1),ylim=c(0,10),xlab="virulence",ylab=expression("fitness ("*R[0]*")"),type="n",cex.lab=2,cex.axis=1.2)
points(A,R0s1,col=viridis(3)[1],type="l",lwd=12)
points(A,R0s2,col=viridis(3)[2],type="l",lwd=12)
points(A,trans.rates3*death.rates3,col=viridis(3)[3],type="l",lwd=12)
mtext("C",side=3,line=1,font=2,adj=0,padj = 0)

par(fig = c(grconvertX(c(.03, .1), from="user", to="ndc"),
            grconvertY(c(6.5, 10), from="user", to="ndc")),
    mar = c(0,0,0,0),
    new = TRUE)
plot(A,R0s1,xlim=c(.0025,.1),ylim=c(0,100),xlab="virulence",ylab=expression("fitness ("*R[0]*")"),type="n",cex.lab=2,cex.axis=1.2)
points(A,R0s1,col=viridis(3)[1],type="l",lwd=12)
points(A,R0s2,col=viridis(3)[2],type="l",lwd=12)
points(A,trans.rates3*death.rates3,col=viridis(3)[3],type="l",lwd=12)
# copy with dimensions 1159 x 621

