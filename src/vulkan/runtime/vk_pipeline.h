#ifndef VK_PIPELINE_H
#define VK_PIPELINE_H

#include "nir/nir.h"
#include "vulkan/vulkan.h"

struct vk_pipeline_robustness_state {
   VkPipelineRobustnessBufferBehaviorEXT storage_buffers;
   VkPipelineRobustnessBufferBehaviorEXT uniform_buffers;
   VkPipelineRobustnessBufferBehaviorEXT vertex_inputs;
   VkPipelineRobustnessImageBehaviorEXT images;
   bool null_uniform_buffer_descriptor;
   bool null_storage_buffer_descriptor;
   bool _pad[2];
};

static inline void
vk_set_subgroup_size(nir_shader *shader,
                     uint32_t subgroup_size,
                     uint32_t min_subgroup_size,
                     uint32_t max_subgroup_size,
                     uint32_t spirv_version,
                     const void *info_pNext,
                     bool allow_varying,
                     bool require_full)
{
   (void)subgroup_size; (void)spirv_version; (void)info_pNext;
   (void)allow_varying; (void)require_full;
   /* A target with a single wave size runs every shader at it. GFX6-9 only have wave64, and
    * radv_shader_choose_subgroup_size() would otherwise pick wave32 for small workgroups. */
   if (min_subgroup_size != 0 && min_subgroup_size == max_subgroup_size) {
      shader->info.min_subgroup_size = min_subgroup_size;
      shader->info.max_subgroup_size = max_subgroup_size;
   }
}

#endif
