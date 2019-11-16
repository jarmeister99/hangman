import sys
import argparse
import numpy as np
import string

# TODO:
# - handle edge case at the end of corpus (see first line of make_pairs)

class Markov:
    def __init__(self, data_file):
        self.corpus = self.make_corpus(data_file)
        self.word_dict = self.make_dict()

    def make_corpus(self, data_file):
       f = open(data_file, encoding='utf8').read()
       return f.split()

    def make_pairs(self):
        for i in range(len(self.corpus) - 2):
            yield (self.corpus[i], (self.corpus[i+1], self.corpus[i+2]))

    def make_dict(self):
        pairs = self.make_pairs()
        word_dict = {}
        for word, followed_by in pairs:
            if word in word_dict.keys():
                word_dict[word].append(followed_by)
            else:
                word_dict[word] = [followed_by]
        return word_dict
    def make_chain(self, terminator, minwords=3, cutoff=10):
        first_word = np.random.choice(self.corpus)
        while first_word.islower():
            first_word = np.random.choice(self.corpus)

        num_words = 0
        chain = [first_word]
        while chain[-1][-1] not in terminator or num_words < minwords:
            i = np.random.choice(len(self.word_dict[chain[-1]]))
            for word in self.word_dict[chain[-1]][i]:
                chain.append(word)
                num_words += 1
                if (num_words < minwords):
                    continue
                if (word[-1] in terminator):
                    return ' '.join(chain)
                if (num_words == cutoff):
                    return ' '.join(chain)
        return ' '.join(chain)

def strip_punctuation(line):
    line = ''.join([c for c in line if c.isalpha() or c.isspace()])
    return line

def main():
    parse = argparse.ArgumentParser(description='Generates a markov chain')
    parse.add_argument('data', metavar='N', type=str, help='The text file the chain learns from')
    parse.add_argument('min', metavar='N', type=int, help='The minimum chain size')
    parse.add_argument('max', metavar='N', type=int, help='The maximum chain size')
    parse.parse_args()
    markov = Markov('data.txt')
    print(strip_punctuation(markov.make_chain('?.!', minwords=5, cutoff=7)).lower());

if __name__ == '__main__':
    main()
