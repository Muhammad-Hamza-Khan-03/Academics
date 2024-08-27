from mrjob.job import MRJob

class alphabets(MRJob):

    def mapper(self, _, line):
        words = line.split()
        for word in words:
            first_letter = word[0].lower()
            yield first_letter, 1

    def reducer(self, key, values):
        yield key, sum(values)

if __name__ == '__main__':
    alphabets.run()