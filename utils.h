/// @brief Depicts relationship between a point and segment
/// 0 = upper endpoint of segment
/// 1 = lower endpoint of segment
/// 2 = lies on segment
/// -1 does not lie on segment
enum point_seg_rel {
    none = -1, U = 0, L = 1, C = 2
};