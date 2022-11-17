from cs50 import get_string

def main():
    text = input("Enter text: ")
    letters = letter_count(text)
    words = word_count(text)
    sentences = sentence_count(text)
    level = calculate_level(text, letters, words, sentences)
    if level < 1:
        print("Before Grade 1")
    elif level >16:
        print("Grade 16+")
    else:
        #level = str(level)
        print(f"Grade {level}")


def letter_count(sentence):
    count = 0
    for l in sentence:
        if l.isalpha():
            count += 1
    return count

def word_count(sentence):
    count = len(sentence.split())
    return count

def sentence_count(sentence):
    count = 0
    for c in sentence:
        if c in {'.', '!', '?'}:
            count += 1
    return count

def calculate_level(sentence, l, w, s):
    L = (l * 100) / w
    S = (s * 100) / w
    index = 0.0588 * L - 0.296 * S - 15.8
    return round(index)

main()
