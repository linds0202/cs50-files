from sys import argv, exit
import csv


def main():
    # check for 2 command line inputs
    if len(argv) != 3:
        print("Missing command line argument")
        exit(1)
    
    # open csv file
    csv_file = open(argv[1], 'r')
    
    # list of possible strands to look for
    strands = []
    # dictionary of people w/counts
    people = {}
    # populate strand and people
    for ind, row in enumerate(csv_file):
        if ind == 0:
            strands = [strand for strand in row.strip().split(',')][1:]
        else:
            current_row = row.strip().split(',')
            people[current_row[0]] = [int(x) for x in current_row[1:]]
    
    # open sequence file and read it in entirety
    sequence = open(argv[2], 'r').read()
    
    # track count of each type of strand in dna sample
    final_strands = []
    
    # iterate through dna sequence looking for contiguous matching strands
    for strand in strands:
        i = 0
        max_strand = -1
        curr_max = 0
        while i < len(sequence):
            # look at slices
            curr_slice = sequence[i:i + len(strand)]
            if curr_slice == strand:
                curr_max += 1
                max_strand = max(max_strand, curr_max)
                i += len(strand)
                pass
            else:
                curr_max = 0
                i += 1
        final_strands.append(max_strand)
    # iterate through dictionary and compare final_strands to their data
    for name, data in people.items():
        if data == final_strands:
            print(name)
            exit(0)
    print("No match")
            
    # print(strand)
    # print(people)
    # print(final_strands)


main()