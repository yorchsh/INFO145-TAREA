bits = input("bits: ")
word_size = int(input("word_size: "))

prev_bits = 0
current_bits = word_size
i = 0
while current_bits < len(bits):
    print(i, ": ", int(bits[prev_bits:current_bits], base=2))
    
    prev_bits = current_bits
    current_bits += word_size
    i += 1