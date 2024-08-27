from mrjob.job import MRJob

class Temp(MRJob):
    def mapper(self,_,lines):
        cust,prod,price=lines.split(",")
        yield cust,float(price)
    def reducer(self,key,value):
        
        yield key,sum(value)
        
if __name__ == "__main__":
    Temp.run()
