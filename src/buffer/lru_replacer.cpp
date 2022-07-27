//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) : num_pages_(num_pages) {
}

LRUReplacer::~LRUReplacer() = default;

auto LRUReplacer::Victim(frame_id_t *frame_id) -> bool {
  if (frame_id_map_.empty()) {
    return false;
  }
  *frame_id = frame_id_list_.front();
  frame_id_list_.pop_front();
  frame_id_map_.erase(*frame_id);
  return true;
}

void LRUReplacer::Pin(frame_id_t frame_id) {
  auto map_iterator =  frame_id_map_.find(frame_id);
  if (map_iterator == frame_id_map_.end()) {
    return;
  }
  frame_id_map_.erase(map_iterator);
  frame_id_list_.erase(map_iterator->second);
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
  auto map_iterator = frame_id_map_.find(frame_id);
  if (map_iterator != frame_id_map_.end()) {
    return;
  }

  frame_id_t evict_frame_id;
  if (Size() == num_pages_) {
    Victim(&evict_frame_id);
  }

  frame_id_list_.push_back(frame_id);
  frame_id_map_.insert(std::make_pair(frame_id, std::prev(frame_id_list_.end())));
}

auto LRUReplacer::Size() -> size_t { return frame_id_map_.size(); }

}  // namespace bustub
