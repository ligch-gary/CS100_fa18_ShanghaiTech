from random import randrange

def init():
    '''create a dict to model three doors and things behind the doors'''
    result = {i: 'goat' for i in range(3)}
    r = randrange(3)
    result[r] = 'car'
    return result

def startGame():
    '''Start the game'''
    doors = init()

    while True:  # get the first guessed door number
        try:
            doorNum = int(input('Choose a door to open:'))
            assert 0<= doorNum <=2
            break
        except:
            print('Door number must be between {} and {}'.format(0, 2))
            
    for door in doors.keys()-{doorNum}:  # host check things behind other doors, and open one door if it is not the door of car
        if doors[door] == 'goat':
            print('"goat" behind the door', door)
            thirdDoor = (doors.keys()-{door, doorNum}).pop()
            while True:
                try:
                    change = input('Switch to {}?(y/n)'.format(thirdDoor))
                    assert change in {'y','n'}
                    break
                except:
                    change = input('Switch to {}?(y/n)'.format(thirdDoor))
            finalDoorNum = thirdDoor if change=='y' else doorNum
            if doors[finalDoorNum] == 'goat':
                return 'I Win!'
            else:
                return 'You Win.'
while True:
    print('='*30)
    print(startGame())
    r = input('Do you want to try once more?(y/n)')
    if r == 'n':
        break
