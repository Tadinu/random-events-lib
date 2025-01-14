#pragma once

#include "sigma_algebra.h"
#include <unordered_set>

/**
 * Enum for border types of simple_sets.
 */
enum class BorderType {

    /**
     * Open indicates that a value is included in the interval.
     */
    OPEN,

    /**
     * Close indicates that a value is excluded in the interval.
     */
    CLOSED

};

/**
 * Logically intersect borders.
 * @param border_1 One of the borders to intersect.
 * @param border_2 The other border to intersect.
 * @return The intersection of the borders.
 */
inline BorderType intersect_borders(BorderType border_1, BorderType border_2) {
    return (border_1 == BorderType::OPEN || border_2 == BorderType::OPEN) ? BorderType::OPEN : BorderType::CLOSED;
}

/**
 * Logically t_complement a border.
 * @param border The borders to t_complement.
 * @return The t_complement a border.
 */
inline BorderType invert_border(BorderType border) {
    return border == BorderType::OPEN ? BorderType::CLOSED : BorderType::OPEN;
}

class Interval; // Forward declaration

/**
 * Class that represents an atomic interval.
 */
class SimpleInterval : public SimpleSetWrapper<Interval, SimpleInterval, float> {
public:
    /**
     * The lower value.
     */
    float lower = 0;

    /**
     * The upper value.
     */
    float upper = 0;

    /**
     * THe left border type.
     */
    BorderType left = BorderType::OPEN;

    /**
     * The right border type.
     */
    BorderType right = BorderType::OPEN;

    /**
     * Construct an atomic interval.
     */
    explicit SimpleInterval(float lower = 0, float upper = 0, BorderType left = BorderType::OPEN,
                            BorderType right = BorderType::OPEN);


    [[nodiscard]] SimpleInterval simple_set_intersection_with(const SimpleInterval &other) const;

    [[nodiscard]] Interval simple_set_complement() const;

    [[nodiscard]] bool simple_set_contains(const float &element) const;

    [[nodiscard]] bool simple_set_is_empty() const;

    /**
     * This method depends on the type of simple set and has to be overloaded.
     *
     * @param other The other simple set.
     * @return True if they are equal.
     */
    bool operator==(const SimpleInterval &other) const;

    std::string to_string();

    explicit operator std::string();

    /**
     * Compare two simple intervals. Simple intervals are ordered by lower bound. If the lower bound is equal, they are
     * ordered by upper bound.
     * @param other The other interval
     * @return True if this interval is less than the other interval.
     */
    bool operator<(const SimpleInterval &other) const override {
        if (lower == other.lower) {
            return upper < other.upper;
        }
        return lower < other.lower;
    }

    /**
    * Compare two simple intervals. Simple intervals are ordered by lower bound. If the lower bound is equal, they are
    * ordered by upper bound.
    * @param other The other interval
    * @return True if this interval is less or equal to the other interval.
    */
    bool operator<=(const SimpleInterval &other) const override {
        if (lower == other.lower) {
            return upper <= other.upper;
        }
        return lower <= other.lower;
    }

};

/**
 * Hash function for simple intervals.
 */
namespace std {
    template<>
    struct hash<SimpleInterval> {
        size_t operator()(const SimpleInterval &interval) const {
            return std::hash<float>()(interval.lower) ^ std::hash<float>()(interval.upper) ^ std::hash<int>()(
                    static_cast<int>(interval.left)) ^ std::hash<int>()(static_cast<int>(interval.right));
        }
    };
}

/**
 * Extend a vector with another vector.
 * @tparam T The type of the vector.
 * @param first The first vector.
 * @param second The second vector.
 */
template<typename T>
void extend_vector(std::vector<T> &first, const std::vector<T> &second) {
    first.reserve(first.size() + distance(second.begin(), second.end()));
    first.insert(first.end(), second.begin(), second.end());
}

/**
 * Class that represents a composite interval.
 * An interval is an (automatically simplified) union of simple simple_sets.
 */
class Interval : public CompositeSetWrapper<Interval, SimpleInterval, float> {

public:

    Interval() = default;

    explicit Interval(const SimpleSetType<SimpleInterval> &simple_sets) {
        this->simple_sets = simple_sets;
        this->empty_simple_set_ptr = &simple_interval;
    }

    explicit Interval(const SimpleInterval &simple_interval) {
        this->simple_sets.insert(simple_interval);
        this->empty_simple_set_ptr = &this->simple_interval;
    }

    Interval composite_set_simplify();

    /**
     * The empty simple interval.
     */
    SimpleInterval simple_interval;
};

inline Interval closed(float lower, float upper) {
    return Interval(
            SimpleSetType<SimpleInterval>{SimpleInterval{lower, upper, BorderType::CLOSED, BorderType::CLOSED}});
}

inline Interval open(float lower, float upper) {
    return Interval(SimpleSetType<SimpleInterval>{SimpleInterval{lower, upper, BorderType::OPEN, BorderType::OPEN}});
}

inline Interval open_closed(float lower, float upper) {
    return Interval(SimpleSetType<SimpleInterval>{SimpleInterval{lower, upper, BorderType::OPEN, BorderType::CLOSED}});
}

inline Interval closed_open(float lower, float upper) {
    return Interval(SimpleSetType<SimpleInterval>{SimpleInterval{lower, upper, BorderType::CLOSED, BorderType::OPEN}});
}

inline Interval singleton(float value) {
    return Interval(
            SimpleSetType<SimpleInterval>{SimpleInterval{value, value, BorderType::CLOSED, BorderType::CLOSED}});
}

inline Interval empty() {
    return Interval(SimpleSetType<SimpleInterval>{});
}

inline Interval reals() {
    return Interval(SimpleSetType<SimpleInterval>{
            SimpleInterval{-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(),
                           BorderType::OPEN, BorderType::OPEN}});
}