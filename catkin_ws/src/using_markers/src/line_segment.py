
import math

class LineSegment():

    def __init__(self, pt1, pt2):
        """Builds a line segment construct from two tuples of points"""

        #Record the input points
        self.pt1 = pt1
        self.pt2 = pt2

    def closest_pt(self, pt):
        """Calculates the closest point from `pt` to the current line segment"""

        _x, _y = pt

        #Takes the dot product of the vector of the line segment and the input `pt` to the start 
        # of the segment. Then normalizes it over the line segment and caps it if it overshot
        x1, y1 = self.pt1
        x2, y2 = self.pt2

        px = x2 - x1
        py = y2 - y1

        len_sq = px**2 + py**2
        dot = (_x - x1) * px + (_y - y1) * py
        normalized = dot / float(len_sq)
        
        if normalized > 1:
            normalized = 1
        elif normalized < 0:
            normalized = 0

        closest_x = x1 + normalized * px
        closest_y = y1 + normalized * py

        return closest_x, closest_y
    
    def shortest_dist(self, pt):
        """Calculates the shortest distance from `pt` to the current line segment"""

        _x, _y = pt
        closest_x, closest_y = self.closest_pt(pt)
        
        dx = closest_x - _x
        dy = closest_y - _y

        return math.sqrt(dx**2 + dy**2)
        
