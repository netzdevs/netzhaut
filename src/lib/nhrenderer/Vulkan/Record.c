// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES ========================================================================================

#include "Record.h"
#include "Pipeline.h"
#include "Descriptor.h"
#include "Buffer.h"

#include "../Common/Macros.h"

#include "../../nhgfx/Base/Viewport.h"
#include "../../nhgfx/Vulkan/GPU.h"

#include <stdlib.h>
#include <string.h>

//// TEXTURE =========================================================================================
//
//static NH_BOOL nh_vk_recordImage(
//    nh_Content *Content_p, nh_html_Node *Node_p, nh_vk_Pipeline *Pipelines_p, nh_vk_Driver *Driver_p,
//    VkCommandBuffer *CommandBuffer_p)
//{
//NH_RENDERER_BEGIN()
//
//    if (Node_p->tag == NH_HTML_TAG_IMG && nh_gfx_textureLoaded(Content_p, nh_html_getSrc(Node_p), NULL))
//    {
//        VkDeviceSize size_p[1] = {0};
//
//        Driver_p->Functions.vkCmdBindPipeline(
//            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
//            Pipelines_p[NH_VK_PIPELINE_IMAGE].Pipeline
//        );
//        
//        Driver_p->Functions.vkCmdBindDescriptorSets(
//            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
//            Pipelines_p[NH_VK_PIPELINE_IMAGE].PipelineLayout, 0, 1, 
//            &nh_vk_getDescriptor(Node_p, NH_VK_DESCRIPTOR_IMAGE)->DescriptorSet,
//            0, VK_NULL_HANDLE
//        );
//
//        Driver_p->Functions.vkCmdBindVertexBuffers(
//            *CommandBuffer_p, 0, 1, 
//            &nh_vk_getBuffer(Node_p, NH_VK_BUFFER_TEXTURE)->Buffer, 
//            size_p
//        );
//        
//        Driver_p->Functions.vkCmdDraw(*CommandBuffer_p, nh_vk_getBuffer(Node_p, NH_VK_BUFFER_TEXTURE)->size / 3, 1, 0, 0);
//
//        NH_CORE_END(NH_TRUE)
//    }
//
//NH_CORE_END(NH_FALSE)
//}

// BACKGROUND ======================================================================================

static void nh_renderer_vk_recordBackground(
    nh_css_Fragment *Fragment_p, nh_vk_GPU *GPU_p, VkCommandBuffer *CommandBuffer_p)
{
NH_RENDERER_BEGIN()

    VkDeviceSize size_p[1] = {0};

    GPU_p->Driver.Functions.vkCmdBindPipeline(
        *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
        GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_COLOR].Pipeline
    );

    GPU_p->Driver.Functions.vkCmdBindDescriptorSets(
        *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
        GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_COLOR].PipelineLayout, 0, 1, 
        &nh_renderer_vk_getDescriptor(Fragment_p->data_p, NH_RENDERER_VK_DESCRIPTOR_BACKGROUND)->DescriptorSet,
        0, VK_NULL_HANDLE
    );

    GPU_p->Driver.Functions.vkCmdBindVertexBuffers(
        *CommandBuffer_p, 0, 1, 
        &nh_renderer_vk_getBuffer(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_BACKGROUND)->Buffer, 
        size_p
    );
   
    GPU_p->Driver.Functions.vkCmdDraw(*CommandBuffer_p, nh_renderer_vk_getBuffer(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_BACKGROUND)->size / 3, 1, 0, 0);

NH_RENDERER_SILENT_END()
}

//// BACKGROUND IMAGE ================================================================================
//
//static void nh_vk_recordBackgroundImage(
//    nh_Content *Content_p, nh_html_Node *Node_p, nh_vk_Pipeline *Pipelines_p, nh_vk_Driver *Driver_p, 
//    VkCommandBuffer *CommandBuffer_p, VkViewport *Viewport_p)
//{
//NH_RENDERER_BEGIN()
//
//    for (int i = 0; i < Node_p->Properties.Background.Images.count; ++i)
//    {
//        NH_RENDERER_Image *Image_p = nh_renderer_getImage(&Node_p->Properties.Background.Images, i);
//
//        nh_html_PixelBox Box = nh_html_getBackgroundImageBox(Content_p, Node_p, Image_p, 0.0f);
//
//        VkOffset2D Offset =
//        {
//            .x = Box.Position.x,
//            .y = Box.Position.y,
//        };
//        VkExtent2D Extent = 
//        {
//            .width  = Box.Size.width,
//            .height = Box.Size.height,
//        };
//        VkRect2D Scissor = 
//        { 
//            .offset = Offset,
//            .extent = Extent,
//        };
//
//        Driver_p->Functions.vkCmdSetScissor(*CommandBuffer_p, 0, 1, &Scissor);
//
//        Driver_p->Functions.vkCmdBindPipeline(
//            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
//            Pipelines_p[NH_VK_PIPELINE_BACKGROUND_IMAGE].Pipeline
//        );
//        
//        Driver_p->Functions.vkCmdBindDescriptorSets(
//            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
//            Pipelines_p[NH_VK_PIPELINE_BACKGROUND_IMAGE].PipelineLayout, 0, 1, 
//            &nh_vk_getDescriptorFromIndex(Node_p, Image_p->descriptor)->DescriptorSet,
//            0, VK_NULL_HANDLE
//        );
//       
//        VkDeviceSize size_p[1] = {0};
//
//        Driver_p->Functions.vkCmdBindVertexBuffers(
//            *CommandBuffer_p, 0, 1, 
//            &nh_vk_getBufferFromIndex(Node_p, Image_p->buffer)->Buffer, 
//            size_p
//        );
//
//        Driver_p->Functions.vkCmdDraw(*CommandBuffer_p, nh_vk_getBufferFromIndex(Node_p, Image_p->buffer)->size / 3, 1, 0, 0);
//
//        Scissor = nh_vk_getDefaultScissor(Content_p); 
//        Driver_p->Functions.vkCmdSetScissor(*CommandBuffer_p, 0, 1, &Scissor);
//    }
//
//NH_RENDERER_SILENT_END()
//}
//
// TEXT ============================================================================================

static void nh_renderer_vk_recordText(
    nh_css_Fragment *Fragment_p, nh_vk_GPU *GPU_p, VkCommandBuffer *CommandBuffer_p)
{
NH_RENDERER_BEGIN()

    GPU_p->Driver.Functions.vkCmdBindPipeline(
        *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
        GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_TEXT_SDF].Pipeline
    );
    VkDeviceSize size_p[1] = {0};

    for (int i = 0; i < Fragment_p->Text.Values.Text.Segments.length; ++i)
    {
        nh_gfx_TextSegment *Segment_p = &((nh_gfx_TextSegment*)Fragment_p->Text.Values.Text.Segments.p)[i];
        if (Segment_p->length <= 0) {continue;}

        GPU_p->Driver.Functions.vkCmdBindVertexBuffers(
            *CommandBuffer_p, 0, 1,
            &(nh_renderer_vk_getBufferFromIndex(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_TEXT_SDF, i)->Buffer), 
            size_p
        );
        
        GPU_p->Driver.Functions.vkCmdBindDescriptorSets(
            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
            GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_TEXT_SDF].PipelineLayout, 
            0, 1, 
            &(nh_renderer_vk_getDescriptorFromIndex(Fragment_p->data_p, NH_RENDERER_VK_DESCRIPTOR_TEXT_SDF, i)->DescriptorSet),
            0, VK_NULL_HANDLE
        );
    
        GPU_p->Driver.Functions.vkCmdBindIndexBuffer(
            *CommandBuffer_p, 
            nh_renderer_vk_getBufferFromIndex(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_TEXT_SDF_INDEX, i)->Buffer, 
            0, VK_INDEX_TYPE_UINT32
        );
    
        GPU_p->Driver.Functions.vkCmdDrawIndexed(
            *CommandBuffer_p, Segment_p->length * 6, 1, 0, 0, 0
        );
    }

NH_RENDERER_SILENT_END()
}

// BORDER ==========================================================================================

static void nh_renderer_vk_recordBorder(
    nh_css_Fragment *Fragment_p, nh_vk_GPU *GPU_p, VkCommandBuffer *CommandBuffer_p)
{
NH_RENDERER_BEGIN()

    if (Fragment_p->Box.Values.borderTop > 0)
    {
        GPU_p->Driver.Functions.vkCmdBindPipeline(
            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
            GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_COLOR].Pipeline
        );
        VkDeviceSize size_p[1] = {0};

        GPU_p->Driver.Functions.vkCmdBindDescriptorSets(
            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
            GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_COLOR].PipelineLayout, 0, 1, 
            &nh_renderer_vk_getDescriptor(Fragment_p->data_p, NH_RENDERER_VK_DESCRIPTOR_TOP_BORDER)->DescriptorSet,
            0, VK_NULL_HANDLE
        );

        GPU_p->Driver.Functions.vkCmdBindVertexBuffers(
            *CommandBuffer_p, 0, 1, 
            &nh_renderer_vk_getBuffer(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_TOP_BORDER_VERTICES)->Buffer, 
            size_p
        );

        GPU_p->Driver.Functions.vkCmdDraw(*CommandBuffer_p, nh_renderer_vk_getBuffer(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_TOP_BORDER_VERTICES)->size / 3, 1, 0, 0);
    }
    if (Fragment_p->Box.Values.borderRight > 0)
    {
        GPU_p->Driver.Functions.vkCmdBindPipeline(
            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
            GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_COLOR].Pipeline
        );
        VkDeviceSize size_p[1] = {0};

        GPU_p->Driver.Functions.vkCmdBindDescriptorSets(
            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
            GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_COLOR].PipelineLayout, 0, 1, 
            &nh_renderer_vk_getDescriptor(Fragment_p->data_p, NH_RENDERER_VK_DESCRIPTOR_RIGHT_BORDER)->DescriptorSet,
            0, VK_NULL_HANDLE
        );

        GPU_p->Driver.Functions.vkCmdBindVertexBuffers(
            *CommandBuffer_p, 0, 1, 
            &nh_renderer_vk_getBuffer(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_RIGHT_BORDER_VERTICES)->Buffer, 
            size_p
        );

        GPU_p->Driver.Functions.vkCmdDraw(*CommandBuffer_p, nh_renderer_vk_getBuffer(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_RIGHT_BORDER_VERTICES)->size / 3, 1, 0, 0);
    }
    if (Fragment_p->Box.Values.borderBottom > 0)
    {
        GPU_p->Driver.Functions.vkCmdBindPipeline(
            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
            GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_COLOR].Pipeline
        );
        VkDeviceSize size_p[1] = {0};

        GPU_p->Driver.Functions.vkCmdBindDescriptorSets(
            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
            GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_COLOR].PipelineLayout, 0, 1, 
            &nh_renderer_vk_getDescriptor(Fragment_p->data_p, NH_RENDERER_VK_DESCRIPTOR_BOTTOM_BORDER)->DescriptorSet,
            0, VK_NULL_HANDLE
        );

        GPU_p->Driver.Functions.vkCmdBindVertexBuffers(
            *CommandBuffer_p, 0, 1, 
            &nh_renderer_vk_getBuffer(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_BOTTOM_BORDER_VERTICES)->Buffer, 
            size_p
        );

        GPU_p->Driver.Functions.vkCmdDraw(*CommandBuffer_p, nh_renderer_vk_getBuffer(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_BOTTOM_BORDER_VERTICES)->size / 3, 1, 0, 0);
    }
    if (Fragment_p->Box.Values.borderLeft > 0)
    {
        GPU_p->Driver.Functions.vkCmdBindPipeline(
            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
            GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_COLOR].Pipeline
        );
        VkDeviceSize size_p[1] = {0};

        GPU_p->Driver.Functions.vkCmdBindDescriptorSets(
            *CommandBuffer_p, VK_PIPELINE_BIND_POINT_GRAPHICS, 
            GPU_p->Renderer.Pipelines_p[NH_RENDERER_VK_PIPELINE_COLOR].PipelineLayout, 0, 1, 
            &nh_renderer_vk_getDescriptor(Fragment_p->data_p, NH_RENDERER_VK_DESCRIPTOR_LEFT_BORDER)->DescriptorSet,
            0, VK_NULL_HANDLE
        );

        GPU_p->Driver.Functions.vkCmdBindVertexBuffers(
            *CommandBuffer_p, 0, 1, 
            &nh_renderer_vk_getBuffer(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_LEFT_BORDER_VERTICES)->Buffer, 
            size_p
        );

        GPU_p->Driver.Functions.vkCmdDraw(*CommandBuffer_p, nh_renderer_vk_getBuffer(Fragment_p->data_p, NH_RENDERER_VK_BUFFER_LEFT_BORDER_VERTICES)->size / 3, 1, 0, 0);
    }

NH_RENDERER_SILENT_END()
}

// RECORD ==========================================================================================

static void nh_renderer_vk_recordTextFragment(
    nh_css_Fragment *Fragment_p, nh_vk_GPU *GPU_p, VkCommandBuffer *CommandBuffer_p)
{
NH_RENDERER_BEGIN()

    nh_renderer_vk_recordText(Fragment_p, GPU_p, CommandBuffer_p);

NH_RENDERER_SILENT_END()
}

static void nh_renderer_vk_recordBoxFragment(
    nh_css_Fragment *Fragment_p, nh_vk_GPU *GPU_p, VkCommandBuffer *CommandBuffer_p)
{
NH_RENDERER_BEGIN()

    if (Fragment_p->Box.Values.BackgroundColor.a > 0.0f) {
        nh_renderer_vk_recordBackground(Fragment_p, GPU_p, CommandBuffer_p);
    }
    nh_renderer_vk_recordBorder(Fragment_p, GPU_p, CommandBuffer_p);

NH_RENDERER_SILENT_END()
}

static void nh_renderer_vk_recordTextFragments(
    nh_css_Fragment *Fragment_p, nh_vk_GPU *GPU_p, VkCommandBuffer *CommandBuffer_p)
{
NH_RENDERER_BEGIN()

    if (Fragment_p->type == NH_CSS_FRAGMENT_TEXT) {
        nh_renderer_vk_recordTextFragment(Fragment_p, GPU_p, CommandBuffer_p);
    }
    for (int i = 0; i < Fragment_p->Children.size; ++i) {
        nh_renderer_vk_recordTextFragments(Fragment_p->Children.pp[i], GPU_p, CommandBuffer_p);
    }

NH_RENDERER_SILENT_END()
}

static void nh_renderer_vk_recordBoxFragments(
    nh_css_Fragment *Fragment_p, nh_vk_GPU *GPU_p, VkCommandBuffer *CommandBuffer_p)
{
NH_RENDERER_BEGIN()

    if (Fragment_p->type == NH_CSS_FRAGMENT_BOX) {
        nh_renderer_vk_recordBoxFragment(Fragment_p, GPU_p, CommandBuffer_p);
    }
    for (int i = 0; i < Fragment_p->Children.size; ++i) {
        nh_renderer_vk_recordBoxFragments(Fragment_p->Children.pp[i], GPU_p, CommandBuffer_p);
    }

NH_RENDERER_SILENT_END()
}

void nh_renderer_vk_recordFragmentTree(
    nh_css_FragmentTree *Tree_p, nh_gfx_Viewport *Viewport_p)
{
NH_RENDERER_BEGIN()

    // render background first;
    for (int i = 0; i < Viewport_p->Vulkan.images; ++i) {
        nh_renderer_vk_recordBoxFragments(
            Tree_p->Root_p, Viewport_p->Surface_p->Vulkan.GPU_p, Viewport_p->Vulkan.CommandBuffers_pp[i] 
        );
    }

    // render text afterwards;
    for (int i = 0; i < Viewport_p->Vulkan.images; ++i) {
        nh_renderer_vk_recordTextFragments(
            Tree_p->Root_p, Viewport_p->Surface_p->Vulkan.GPU_p, Viewport_p->Vulkan.CommandBuffers_pp[i] 
        );
    }

NH_RENDERER_SILENT_END()
}

