from random import sample
from math import pi
from cryptography.fernet import Fernet
from itertools import zip_longest
from requests import get


def change(cents):
    US_COIN_DENOMINATIONS = (25, 10, 5, 1)

    if cents < 0:
        raise ValueError('amount cannot be negative')

    result = []
    for d in US_COIN_DENOMINATIONS:
        result.append(cents // d)
        cents %= d

    return tuple(result)


def stretched(s):
    s = ''.join(s.split())
    return ''.join((c * (i+1)) for i, c in enumerate(s))


def scramble(s):
    return ''.join(sample(s, len(s)))


class Cylinder:
    def __init__(self, radius=1, height=1):
        self.radius = radius
        self.height = height

    @property
    def volume(self):
        return pi * (self.radius ** 2) * self.height

    @property
    def surface_area(self):
        return 2 * pi * self.radius * (self.height + self.radius)

    def widen(self, factor):
        self.radius *= factor
        return self

    def stretch(self, factor):
        self.height *= factor
        return self


def powers(base, limit):
    power = 1
    while power <= limit:
        yield power
        power *= base
    return


def say(first=None):
    if first is None:
        return ''

    def sayNext(next=None):
        if next is None:
            return first
        return say(f'{first} {next}')

    return sayNext


def interleave(a, *b):
    return [item for pair in zip_longest(a, b) for item in pair if item is not None]


def make_crypto_functions(key):
    return ((cipher := Fernet(key)).encrypt, cipher.decrypt)


def top_ten_scorers(stats):
    flattened_stats = [[team, name, num_games, points] for team in stats.keys()
                       for name, num_games, points in stats[team]
                       if num_games >= 15]

    stats = [{
        'name': name,
        'ppg': points / num_games,
        'team': team
    } for team, name, num_games, points in flattened_stats]

    return sorted(stats, key=lambda player: player['ppg'], reverse=True)[:10]


def studio_ghibli_characters(*, hair_color, gender):
    query = {
        'hair_color': hair_color,
        'gender': gender
    }

    response = get('https://ghibliapi.herokuapp.com/people', params=query)

    response.raise_for_status()

    return [{k: v for k, v in person.items()
             if k in {'name', 'gender', 'age', 'eye_color', 'hair_color'}}
            for person in response.json()]
