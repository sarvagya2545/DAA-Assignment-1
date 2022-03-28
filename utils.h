// depicts relationship between a point and segment
// 0 = upper endpoint of segment
// 1 = lower endpoint of segment
// 2 = lies on segment
// -1 does not lie on segment
enum point_seg_rel {
    none = -1, upper = 0, lower = 1, on = 2
};