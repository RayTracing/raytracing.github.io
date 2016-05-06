#ifndef BVHH
#define BVHH

#include "hitable.h"

class bvh_node : public hitable  {
    public:
        bvh_node() {}
        bvh_node(hitable **l, int n, float time0, float time1);
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        virtual bool bounding_box(float t0, float t1, aabb& box) const;
        hitable *left;
        hitable *right;
        aabb box;
};


bool bvh_node::bounding_box(float t0, float t1, aabb& b) const {
    b = box;
    return true;
}

bool bvh_node::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    if (box.hit(r, t_min, t_max)) {
        hit_record left_rec, right_rec;
        bool hit_left = left->hit(r, t_min, t_max, left_rec);
        bool hit_right = right->hit(r, t_min, t_max, right_rec);
        if (hit_left && hit_right) {
            if (left_rec.t < right_rec.t) 
                rec = left_rec;
            else 
                rec = right_rec;
            return true;
        }
        else if (hit_left) {
            rec = left_rec;
            return true;
        }
        else if (hit_right) {
            rec = right_rec;
            return true;
        }
        else 
            return false;
    }
    else return false;
}


int box_x_compare (const void * a, const void * b) {
    aabb box_left, box_right;
    hitable *ah = *(hitable**)a;
    hitable *bh = *(hitable**)b;
    if(!ah->bounding_box(0,0, box_left) || !bh->bounding_box(0,0, box_right))
        std::cerr << "no bounding box in bvh_node constructor\n";
    if ( box_left.min().x() - box_right.min().x() < 0.0  )
        return -1;
    else
        return 1;
}

int box_y_compare (const void * a, const void * b)
{
    aabb box_left, box_right;
    hitable *ah = *(hitable**)a;
    hitable *bh = *(hitable**)b;
    if(!ah->bounding_box(0,0, box_left) || !bh->bounding_box(0,0, box_right))
        std::cerr << "no bounding box in bvh_node constructor\n";
    if ( box_left.min().y() - box_right.min().y() < 0.0  )
        return -1;
    else
        return 1;
}
int box_z_compare (const void * a, const void * b)
{
    aabb box_left, box_right;
    hitable *ah = *(hitable**)a;
    hitable *bh = *(hitable**)b;
    if(!ah->bounding_box(0,0, box_left) || !bh->bounding_box(0,0, box_right))
        std::cerr << "no bounding box in bvh_node constructor\n";
    if ( box_left.min().z() - box_right.min().z() < 0.0  )
        return -1;
    else
        return 1;
}


bvh_node::bvh_node(hitable **l, int n, float time0, float time1) {
    aabb *boxes = new aabb[n];
    float *left_area = new float[n];
    float *right_area = new float[n];
    aabb main_box;
    bool dummy = l[0]->bounding_box(time0,time1,main_box);
    for (int i = 1; i < n; i++) {
        aabb new_box;
        bool dummy = l[i]->bounding_box(time0,time1,new_box);
        main_box = surrounding_box(new_box, main_box);
    }
    int axis = main_box.longest_axis();
    if (axis == 0)
        qsort(l, n, sizeof(hitable *), box_x_compare);
    else if (axis == 1)
        qsort(l, n, sizeof(hitable *), box_y_compare);
    else
        qsort(l, n, sizeof(hitable *), box_z_compare);
    for (int i = 0; i < n; i++)
        bool dummy = l[i]->bounding_box(time0,time1,boxes[i]);
    left_area[0] = boxes[0].area();
    aabb left_box = boxes[0];
    for (int i = 1; i < n-1; i++) {
        left_box = surrounding_box(left_box, boxes[i]);
        left_area[i] = left_box.area(); 
    }
    right_area[n-1] = boxes[n-1].area();
    aabb right_box = boxes[n-1];
    for (int i = n-2; i > 0; i--) {
        right_box = surrounding_box(right_box, boxes[i]);
        right_area[i] = right_box.area(); 
    }
    float min_SAH = FLT_MAX;
    int min_SAH_idx;
    for (int i = 0; i < n-1; i++) {
        float SAH = i*left_area[i] + (n-i-1)*right_area[i+1];
        if (SAH < min_SAH) {
            min_SAH_idx = i;
            min_SAH = SAH;
        }
    }

/*
    if (min_SAH_idx == 0) 
        left = l[0];
    else
        left = new bvh_node(l, min_SAH_idx+1, time0, time1);
    if (min_SAH_idx == n-2) 
        right = l[min_SAH_idx+1];
    else
        right = new bvh_node(l + min_SAH_idx+1, n - min_SAH_idx -1, time0, time1);
        */
        if (n == 1) {
                    left = right = l[0];
                        }
                            else if (n == 2) {
                                        left = l[0];
                                                right = l[1];
                                                    }
                                                        else {
                                                                    left = new bvh_node(l, n/2, time0, time1);
                                                                            right = new bvh_node(l + n/2, n - n/2, time0, time1);
                                                                                }

    box = main_box;
}

#endif

