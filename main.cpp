#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#define PI 3.14159265
sf::Color color = sf::Color::Magenta;

struct Line {
  double len;
  double x, y;
  sf::RectangleShape line;
  double rotate;
  Line *next, *prev;
};

void add(Line *&L, Line q) {
  Line *p = new Line;
  p->len = q.len;
  p->line = q.line;
  p->rotate = q.rotate;
  p->x = q.x;
  p->y = q.y;
  p->next = nullptr;
  p->prev = nullptr;
  if (L == nullptr) {
    L = p;
    return;
  }
  p->next = L->next;
  p->prev = L;
  if (L->next != nullptr) {
    L->next->prev = p;
  }
  L->next = p;
  return;
}

void update(sf::RectangleShape &line, Line ln) {
  line.move(ln.x, ln.y);
  line.setSize(sf::Vector2f(ln.len, 1.0));
  line.rotate(ln.rotate);
  line.setFillColor(color);
  return;
}

void Draw(sf::RenderWindow &window, std::vector<Line *> &vec, int count) {
  if (count > 5) {
    return;
  }
  window.clear(sf::Color::Black);
  for (int i = 0; i < vec.size(); ++i) {
    for (Line *p = vec[i]; p != nullptr; p = p->next) {
      window.draw(p->line);
    }
  }
  window.display();
  sf::sleep(sf::seconds(1));
  for (int i = 0; i < vec.size(); ++i) {
    for (Line *q = vec[i]; q != nullptr;) {
      Line ln1, ln2, ln3, ln4;
      ln1.len = q->len / 3.0;

      ln2.len = ln1.len;
      ln3.len = ln1.len;
      ln4.len = ln1.len;
      ln2.rotate = q->rotate - 60;
      ln3.rotate = q->rotate + 60;
      ln4.rotate = q->rotate;
      ln4.x = q->x + 2 * ln1.len * cos(q->rotate * PI / 180);
      ln4.y = q->y + 2 * ln1.len * sin(q->rotate * PI / 180);

      ln2.x = q->x + ln1.len * cos(q->rotate * PI / 180);
      ln2.y = q->y + ln1.len * sin(q->rotate * PI / 180);

      ln3.x = ln2.x + ln1.len * cos(ln2.rotate * PI / 180);
      ln3.y = ln2.y + ln1.len * sin(ln2.rotate * PI / 180);

      q->len = ln1.len;
      q->line.setSize(sf::Vector2f(q->len, 1.0));
      update(ln2.line, ln2);
      update(ln3.line, ln3);
      update(ln4.line, ln4);
      Line *t = q;
      add(t, ln2);
      t = t->next;
      add(t, ln3);
      t = t->next;
      add(t, ln4);
      t = t->next;
      q = t->next;
    }
  }
  Draw(window, vec, count + 1);
  return;
}

int main() {
  Line *sn1 = nullptr;
  Line *sn2 = nullptr;
  Line *sn3 = nullptr;
  sf::RenderWindow window(sf::VideoMode(800, 800), "Snowflake");
  std::vector<Line *> lines(3);
  std::vector<Line> v(3);
  v[0].rotate = 300;
  v[1].rotate = 60;
  v[2].rotate = 180;
  v[0].len = 400;
  v[1].len = 400;
  v[2].len = 400;

  v[0].x = 200;
  v[0].y = (800 - sqrt(3) / 2 * 400) / 2.0 + sqrt(3) / 2 * 400.0;
  v[1].x = 400;
  v[1].y = (800 - sqrt(3) / 2 * 400) / 2.0;
  v[2].x = 600;
  v[2].y = (800 - sqrt(3) / 2 * 400) / 2.0 + sqrt(3) / 2 * 400.0;

  for (int i = 0; i < v.size(); ++i) {
    v[i].line.rotate(v[i].rotate);
    v[i].line.setFillColor(color);
    v[i].line.move(v[i].x, v[i].y);
    v[i].line.setSize(sf::Vector2f(v[i].len, 1.0));
    add(lines[i], v[i]);
  }

  Draw(window, lines, 0);

  while (window.isOpen()) {
    window.clear(sf::Color::Black);
    for (int i = 0; i < lines.size(); ++i) {
      for (Line *p = lines[i]; p != nullptr; p = p->next) {
        window.draw(p->line);
      }
    }
    window.display();
  }
  return 0;
}
