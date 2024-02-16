import random

CATEGORIES = {
    'animals': ['tiger', 'elephant', 'kangaroo', 'dog', 'cat', 'mouse', 'horse', 'cow', 'chicken', 'sheep',
                'pig', 'goat', 'duck', 'deer', 'bear', 'frog', 'fish', 'shark', 'dolphin', 'whale',
                'eagle', 'owl', 'lizard', 'snake', 'bee', 'butterfly', 'ant', 'sparrow', 'turkey', 'penguin'],

    'fruits': ['apple', 'banana', 'cherry', 'date', 'elderberry', 'fig', 'grape', 'honeydew', 'kiwi', 'lemon',
               'mango', 'nectarine', 'orange', 'papaya', 'quince', 'raspberry', 'strawberry', 'tangerine', 'ugli', 'victoria plum',
               'watermelon', 'xigua', 'yellow passion fruit', 'zucchini', 'apricot', 'blackberry', 'coconut', 'durian', 'elderberry', 'guava'],

    'vehicles': ['car', 'truck', 'airplane', 'bicycle', 'bus', 'motorcycle', 'scooter', 'train', 'boat', 'helicopter',
                 'submarine', 'jet ski', 'van', 'tram', 'golf cart', 'tank', 'hovercraft', 'space shuttle', 'snowmobile', 'glider',
                 'limousine', 'ambulance', 'fire engine', 'police car', 'taxi', 'pickup', 'tractor', 'trailer', 'skateboard', 'segway'],

    'colors': ['red', 'blue', 'green', 'yellow', 'purple', 'orange', 'pink', 'brown', 'black', 'white',
               'gray', 'violet', 'indigo', 'maroon', 'turquoise', 'tan', 'beige', 'peach', 'mustard', 'navy',
               'aquamarine', 'coral', 'fuchsia', 'gold', 'silver', 'lime', 'olive', 'burgundy', 'teal', 'magenta'],

    'countries': ['china', 'india', 'indonesia', 'pakistan', 'brazil', 'nigeria', 'bangladesh', 'russia', 'mexico',
                  'japan', 'ethiopia', 'philippines', 'egypt', 'vietnam', 'turkey', 'iran', 'germany', 'thailand',
                  'france', 'italy', 'tanzania', 'myanmar', 'kenya', 'colombia', 'spain', 'greece', 'portugal',
                  'nepal', 'cuba', 'norway']
}

def choose_word(category):
    return random.choice(CATEGORIES[category])

def wordle(correct_word):
    correct_letters = list(correct_word)
    attempt = 0
    user_input = None
    print("Correct letters in correct position are put in (). Correct letters in the wrong position are put in [].")
    print("_ " * len(correct_word))
    while user_input != correct_word:
        user_input = input("Enter your guess: ").lower()
        if len(user_input) != len(correct_word):
            print(f"Please enter a word of exactly {len(correct_word)} letters.")
            continue

        attempt += 1
        feedback = ['_'] * len(correct_word)  # Initialize feedback with placeholders

        for i, letter in enumerate(user_input):
            if i < len(correct_word) and letter == correct_letters[i]:
                feedback[i] = f'({letter})'  # Correct letter in the correct position
            elif letter in correct_word:
                feedback[i] = f'[{letter}]'  # Correct letter in the wrong position
            else:
                feedback[i] = letter  # Incorrect letter

        print(' '.join(feedback))

    if user_input == correct_word:
        print("Congratulations, you guessed the word!")

    score = max(0, 110 - attempt * 10)
    return score

def hangman(correct_word):
    correct_letters = list(correct_word)
    guessed_letters = ['_'] * len(correct_word)
    attempts = 6
    used_letters = set()
    user_input = None
    score = 0
    print("Welcome to Hangman!")
    print(' '.join(guessed_letters), f" - You have {attempts} incorrect attempts remaining.")

    while attempts > 0 and '_' in guessed_letters:
        user_input = input("Guess a letter or the whole word: ").lower()
        attempts -= 1
        # User guesses the entire word
        if len(user_input) == len(correct_word):
            if user_input == correct_word:
                guessed_letters = list(correct_word)
                print("Congratulations, you guessed the word!")
                break
            else:
                print("That's not the word.")

        # User guesses a letter
        elif len(user_input) == 1:
            if user_input in used_letters:
                print("You have already guessed that letter. Try again.")
            elif user_input in correct_word:
                for i, letter in enumerate(correct_word):
                    if letter == user_input:
                        guessed_letters[i] = user_input
                used_letters.add(user_input)
            else:
                used_letters.add(user_input)
                print(f"Incorrect guess. You have {attempts} incorrect attempts left.")
        else:
            print("Please enter only a single letter or the whole word.")

        print(' '.join(guessed_letters))

    if '_' not in guessed_letters:
        print("Congratulations, you guessed the word!")
        score = max(0, 110 - (6 - attempts) * 10)
        return score
    else:
        print(f"Game over. The correct word was '{correct_word}'.")
        score = 0

def display_menu(top_score, top_player):
    print("____________________________________\n")
    print("Welcome to the Word Games!")
    print(f"Current Top Score: {top_score} by {top_player}")
    print("1. Play Wordle")
    print("2. Play Hangman")
    print("3. Exit")
    print("____________________________________")

def read_top_score():
    try:
        with open('top_score.txt', 'r') as file:
            line = file.readline().strip().split(',')
            return int(line[0]), line[1]  # score, player
    except FileNotFoundError:
        return 0, "No one yet"  # Default values

def write_top_score(score, player):
    with open('top_score.txt', 'w') as file:
        file.write(f"{score},{player}")

def main():
    top_score, top_player = read_top_score()
    print(f"Current Top Score: {top_score} by {top_player}")

    while True:
        display_menu(top_score, top_player)
        choice = input("Enter your choice: ")

        if choice == '3' or choice == 'exit' or choice == 'Exit':
            print("Thank you for playing!")
            break

        player_name = input("Enter your player name: ")
        category_choice = input("Choose a category (animals/fruits/vehicles/colors/countries): ").lower()
        correct_word = choose_word(category_choice)

        if choice == '1' or choice == 'wordle' or choice == 'Wordle':
            print(f"Welcome to Wordle, {player_name}!")
            score = wordle(correct_word)
            print(f"{player_name}, your Wordle Game Score: {score}")
        elif choice == '2' or choice == 'hangman' or choice == 'Hangman':
            print(f"Welcome to Hangman, {player_name}!")
            score = hangman(correct_word)
            print(f"{player_name}, your Hangman Score: {score}")
        else:
            print("Invalid choice.")
            continue

        if score > top_score:
            top_score, top_player = score, player_name
            write_top_score(score, player_name)
            print(f"New top score: {top_score} by {top_player}")

if __name__ == "__main__":
    main()
