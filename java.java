import java.util.*;

class Rectangle {
    int x0, y0, x1, y1;

    Rectangle(int x0, int y0, int x1, int y1) {
        this.x0 = x0;
        this.y0 = y0;
        this.x1 = x1;
        this.y1 = y1;
    }
}

class Event implements Comparable<Event> {
    int x;
    int y0, y1;
    boolean isStart;

    Event(int x, int y0, int y1, boolean isStart) {
        this.x = x;
        this.y0 = y0;
        this.y1 = y1;
        this.isStart = isStart;
    }

    @Override
    public int compareTo(Event o) {
        return Integer.compare(this.x, o.x);
    }
}

class SweepLine {
    public static void main(String[] args) {
        List<Rectangle> rectangles = new ArrayList<>();
        rectangles.add(new Rectangle(1, 1, 1, 1));
        rectangles.add(new Rectangle(1, 1, 2,2));
        rectangles.add(new Rectangle(1, 1, 2, 3));
        rectangles.add(new Rectangle(1, 1, 3, 2));
        rectangles.add(new Rectangle(1, 1, 4, 4));
        rectangles.add(new Rectangle(1, 2, 2, 3));
        rectangles.add(new Rectangle(2, 2, 2, 2));
        rectangles.add(new Rectangle(2, 2, 2, 3));
        rectangles.add(new Rectangle(2, 2, 3, 3));
        rectangles.add(new Rectangle(2, 2, 3, 7));
        rectangles.add(new Rectangle(3, 3, 4, 4));
        rectangles.add(new Rectangle(3, 3, 6, 6));
        rectangles.add(new Rectangle(4, 4, 5, 5));
        rectangles.add(new Rectangle(4, 4, 5, 6));
        rectangles.add(new Rectangle(4, 4, 6, 5));
        rectangles.add(new Rectangle(4, 4, 6, 6));
        rectangles.add(new Rectangle(4, 5, 5, 6));
        rectangles.add(new Rectangle(5, 5, 6, 6));
        rectangles.add(new Rectangle(9, 9, 9, 9));
        System.out.println("Total area: " + getTotalArea(rectangles));
    }

    private static int getTotalArea(List<Rectangle> rectangles) {
        List<Event> events = new ArrayList<>();
        for (Rectangle r : rectangles) {
            events.add(new Event(r.x0, r.y0, r.y1, true));//Left bound
            events.add(new Event(r.x1, r.y0, r.y1, false));//Right bound
        }
        Collections.sort(events);

        TreeMap<Integer, Integer> yMap = new TreeMap<>();
        int prevX = 0;
        int totalArea = 0;

        for (Event e : events) {
            int coveredHeight = getCoveredHeight(yMap);
            totalArea += coveredHeight * (e.x - prevX);

            if (e.isStart) {
                yMap.put(e.y0, yMap.getOrDefault(e.y0, 0) + 1);
                yMap.put(e.y1, yMap.getOrDefault(e.y1, 0) - 1);
            } else {
                yMap.put(e.y0, yMap.get(e.y0) - 1);
                yMap.put(e.y1, yMap.get(e.y1) + 1);
            }

            prevX = e.x;
        }

        return totalArea;
    }

    private static int getCoveredHeight(TreeMap<Integer, Integer> yMap) {
        int coveredHeight = 0;
        int count = 0;
        int prevY = 0;

        for (Map.Entry<Integer, Integer> entry : yMap.entrySet()) {
            if (count > 0) {
                coveredHeight += entry.getKey() - prevY;
            }
            count += entry.getValue();
            prevY = entry.getKey();
        }

        return coveredHeight;
    }
}
