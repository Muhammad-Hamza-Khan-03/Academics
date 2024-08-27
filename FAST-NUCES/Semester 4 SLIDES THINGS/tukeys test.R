#One way Anova

rm(list=ls())
Methods=c("Onichan","FIver","Frelance")
y1=c(23,26,20,17)
y2=c(18,28,17,21)
y3=c(16,25,12,14)

y=c(y1,y2,y3)

fc=rep(Methods,each=4)#This line creates a factor vector 
#indicating which method each observation belongs to.

data = data.frame(fc,y);data
#This line creates a data frame containing the factor vector and the scores vector.

anv=aov(y~fc)
#This line performs an ANOVA analysis with scores as the response variable and methods as the factor variable.

summary(anv)

res=residuals(anv)

qqnorm(res)

plot(res)
ycp=y-res

plot(ycp,res)


TukeyHSD(anv,"fc",0.05)
TukeyHSD(anv,"fc",0.05)
###############################
rm(list=ls())

Methods=c("A","B","C")

y1=c(58,64,55,66,67)

y2=c(58,69,71,64,68)

y3=c(48,57,59,47,49)

y=c(y3,y2,y1)

fc=rep(Methods,each=5)

data=data.frame(fc,y) ; data

anv=aov(y~fc)

summary(anv)

res=residuals(anv)

qqnorm(res)

plot(res)

ycp=y-res

plot(ycp,res)

TukeyHSD(anv,"fc",0.05)

####################################
rm(list=ls())

cp=c("1","2","3","4","5","6")

ctp=rep(cp,each=4)

nt=c("nt1","nt2","nt3","nt4")

ntp=rep(nt,6)

y=c(1,1,3,2,3,4,6,3,6,4,7,2,4,8,8,3,3,5,4,2,2,1,3,1)

df=data.frame(ctp,ntp,y)

an=aov(y~ctp+ntp)

summary(an)

mct=TukeyHSD(an,"ctp",0.05)

mct

plot(mct)

res=residuals(an)

qqnorm(res)

plot(res)

ycp=y-res

plot(ycp,res)

pairwise.t.test(y, ctp,.adj="bonf“)