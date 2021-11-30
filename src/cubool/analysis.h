#pragma once
#include <vector>
#include <cfg.h>
#include "GpuBoolMatrix.h"

void cubool_analyse(std::vector<std::shared_ptr<Node<std::set<std::string>>>>& nodes);