from mrjob.job import MRJob

class Temp(MRJob):
    def mapper(self,_,lines):
        cust,price=lines.split(",")
        yield cust,int(price)
    def combiner(self,key,value):
        maxi=0
        for v in value:
            if v > maxi:
                maxi=0
        yield key,maxi
    def reducer(self,key,value):
        maxi=0
        for v in value:
            if v > maxi:
                maxi=v
        yield key,maxi
        
        
if __name__ == "__main__":
    Temp.run()
