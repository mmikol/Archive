import { createCipheriv, createDecipheriv } from 'crypto'
import fetch from 'node-fetch'

export function change(amount) {
  if (amount < 0) {
    throw new RangeError('amount cannot be negative.')
  }

  const US_COIN_DENOMINATIONS = [25, 10, 5, 1]
  const result = []

  US_COIN_DENOMINATIONS.forEach(d => {
    result.push(Math.floor(amount / d))
    amount %= d
  })

  return result
}

export function stretched(str) {
  let result = ''

  str = str.replace(/\s/g, '')

  for (let i = 0; i < str.length; i++) {
    result += str[i].repeat(i + 1)
  }

  return result
}

// Implementing the Durstenfeld Shuffle
export function scramble(str) {
  str = str.split('')

  for (let i = str.length - 1; i > 0; i--) {
    const swap = Math.floor(Math.random() * (i + 1))
    ;[str[i], str[swap]] = [str[swap], str[i]]
  }

  return str.join('')
}

export function powers(base, limit, callback) {
  let power = 1
  while (power <= limit) {
    callback(power)
    power *= base
  }
}

export function* powersGenerator(base, limit) {
  let power = 1
  while (power <= limit) {
    yield power
    power *= base
  }
}

export function say(str1) {
  const result = []

  function addMoreWords(str2) {
    if (str2 === undefined) {
      return result.join(' ')
    }
    result.push(str2)
    return addMoreWords
  }

  return addMoreWords(str1)
}

export function interleave(arr, ...args) {
  const result = [],
    len = Math.min(arr.length, args.length)

  for (let i = 0; i < len; i++) {
    result.push(arr[i], args[i])
  }

  result.push(...arr.slice(len), ...args.slice(len))

  return result
}

export function makeCryptoFunctions(key, algorithm, iv) {
  const encrypt = decrypted => {
    const cipher = createCipheriv(algorithm, key, iv)
    let encrypted = cipher.update(decrypted, 'utf8', 'hex')
    encrypted += cipher.final('hex')
    return encrypted
  }

  const decrypt = encrypted => {
    const decipher = createDecipheriv(algorithm, key, iv)
    let decrypted = decipher.update(encrypted, 'hex', 'utf8')
    decrypted += decipher.final('utf8')
    return decrypted
  }
  return [encrypt, decrypt]
}

export function topTenScorers(stats) {
  return Object.entries(stats)
    .flatMap(pair => pair[1].map(player => [...player, pair[0]]))
    .filter(player => player[1] >= 15)
    .map(player => {
      return {
        name: player[0],
        ppg: player[2] / player[1],
        team: player[3],
      }
    })
    .sort((player1, player2) => {
      return player2.ppg - player1.ppg
    })
    .slice(0, 10)
}

export async function multiply(x, y) {
  const url = `https://ordinary-hazel-pink.glitch.me/multiply?x=${x}&y=${y}`
  const response = await fetch(url)
  const parsed = await response.json()

  if (!response.ok) {
    throw parsed
  }

  return parsed.result
}
