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

        num_words = 1
        chain = [first_word]
        print(f'Starting chain with {first_word}')
        while True:
            # Choose a random pair of words that have followed the last word before
            i = np.random.choice(len(self.word_dict[chain[-1]]))
            # For each word (2 words total) in the tuple:
            for word in self.word_dict[chain[-1]][i]:
                # If the number of words we have is equal to the cut off number...
                if (num_words == cutoff):
                    return ' '.join(chain)
                # Add the word to the chain
                print(f'Adding word {word}')
                chain.append(word)
                num_words += 1
                # If we have the minimum number of words and the word we just added is a terminator
                if (num_words >= minwords and word[-1] in terminator):
                    return ' '.join(chain)


def make_alpha(line):
    line = ''.join([c for c in line if c.isalpha() or c.isspace()])
    return line

def main():
    parse = argparse.ArgumentParser(description='Generates a markov chain')
    parse.add_argument('data', metavar='data', type=str, help='The text file the chain learns from')
    parse.add_argument('--min', metavar='min', type=int, default=5, help='The minimum chain size')
    parse.add_argument('--max', metavar='max', type=int, default=10, help='The maximum chain size')
    args = parse.parse_args()
 
    if (args.min > 0 and args.max > 0):
        if args.min > args.max:
            print('Error: min must be less than or equal to max')
            return

    markov = Markov(args.data)
    print(f'min: {args.min}, max: {args.max}')
    print(make_alpha(markov.make_chain('?.!', minwords=args.min, cutoff=args.max, numbers=False)).lower());

if __name__ == '__main__':
    main()
