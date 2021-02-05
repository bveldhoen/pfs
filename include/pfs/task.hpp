/*
 *  Copyright 2020-present Daniel Trugman
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef PFS_TASK_HPP
#define PFS_TASK_HPP

#include <set>
#include <string>

#include "net.hpp"
#include "types.hpp"

namespace pfs {

class task final
{
public:
    task(const task&) = default;
    task(task&&)      = default;
    task& operator=(const task&) = default;
    task& operator=(task&&) = default;

    bool operator<(const task& rhs) const;

public: // Static utilities
    static bool is_kernel_thread(const stat& st);

public: // Properties
    int id() const;
    const std::string& dir() const;

public: // Getters
    std::vector<std::string> get_cmdline(size_t max_size = 65536) const;

    std::string get_comm() const;

    std::string get_cwd() const;

    std::unordered_map<std::string, std::string>
    get_environ(size_t max_size = 65536) const;

    std::string get_exe() const;

    std::unordered_map<int, std::string> get_fds() const;

    std::set<mem_region> get_maps() const;

    std::set<mount> get_mountinfo() const;

    net get_net() const;

    std::unordered_map<std::string, ino_t> get_ns() const;

    std::string get_root() const;

    stat get_stat() const;

    mem_stats get_statm() const;

    status get_status() const;

    std::set<task> get_tasks() const;

private:
    friend class procfs;
    task(const std::string& procfs_root, int id);

private:
    static std::string build_task_root(const std::string& procfs_root, int id);

private:
    const int _id;
    const std::string _procfs_root;
    const std::string _task_root;
};

} // namespace pfs

#endif // PFS_TASK_HPP
