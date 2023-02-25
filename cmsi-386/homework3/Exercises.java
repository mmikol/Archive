import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.function.Consumer;
import java.util.stream.IntStream;
import java.util.Optional;
import java.util.Map;

public class Exercises {
  public static List<Integer> change(int amount) {
    if (amount < 0) {
      throw new IllegalArgumentException("Amount cannot be negative");
    }

    var US_COIN_DENOMINATIONS = List.of(25, 10, 5, 1);
    var change = new ArrayList<Integer>();

    for (var denomination : US_COIN_DENOMINATIONS) {
      change.add(amount / denomination);
      amount %= denomination;
    }

    return List.copyOf(change);
  }

  public static String stretched(String s) {
    var result = new StringBuilder();

    s = s.replaceAll("\\s", "");
    
    for (int i = 0, charIndex = 0; charIndex < s.length(); i++) {
      var codepoint = s.codePointAt(charIndex);
      var offset = Character.charCount(codepoint);

      for (int j = 0; j < i + 1; j++) {
        result.appendCodePoint(codepoint);
      }
    
      charIndex += offset;
    }

    return result.toString();
  }

  public static <T, U> Set<U> mapThenUnique(List<T> list, Function<T, U> mapper) {
    return list
              .stream()
              .map(mapper::apply)
              .collect(Collectors.toSet());
  }

  public static void powers(int base, int limit, Consumer<Integer> consumer) {
    for (var power = 1; power <= limit; power *= base) {
      consumer.accept(power);
    }
  }

  public static IntStream powers(int base) {
    return IntStream.iterate(1, power -> base * power);
  }

  static class Sayer {
    static String words;

    Sayer(String firstWord) {
      words = firstWord;
    }

    static Sayer and(String nextWord) {
      return new Sayer(words + " " + nextWord);
    };

    static String ok() {
      return words;
    };
  }

  public static String say() {
    return "";
  }

  public static Sayer say(String firstWord) {
    return new Sayer(firstWord);
  }

  public static <T> T twice(Function<T, T> f, T x) {
    return f.apply(f.apply(x));
  }

  public static Optional<String> firstLongStringUppercased(int min_length, List<String> strings) {
    return strings
                .stream()
                .filter(s -> s.length() > min_length)
                .findFirst()
                .map(String::toUpperCase);
  }

  // Credit to Dr. Toal for the class idea
  static class Player {
    String name;
    String team;
    int games;
    int points;
    double ppg() { return (double) this.points / this.games; };

    Player(String name, int games, int points, String team) {
      this.name = name;
      this.games = games;
      this.team = team;
      this.points = points;
    }
  }

  public static List<String> topTenScorers(Map<String, List<String>> stats) {
    return stats
              .entrySet()
              .stream()
              .flatMap((teams) -> teams.getValue().stream().map(player -> String.format("%s,%s", player, teams.getKey())))
              .map(p -> p.split(","))
              .map(p -> new Player(p[0], Integer.parseInt(p[1]), Integer.parseInt(p[2]), p[3]))
              .filter(p -> p.games >= 15)
              .sorted((p1, p2) -> Double.compare(p2.ppg(), p1.ppg()))
              .limit(10)
              .map(p -> String.format("%s|%.2f|%s", p.name, p.ppg(), p.team))
              .collect(Collectors.toList());
  }
}