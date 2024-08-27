from mrjob.job import MRJob

class Lengthfive(MRJob):

    def mapper(self, _, line):
        words = line.split()
        for word in words:
            if len(word) == 5:
                yield word, 1

    def reducer(self, key, values):
        yield key, sum(values)

if __name__ == '__main__':
    Lengthfive.run()