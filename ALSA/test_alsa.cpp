#include <alsa/asoundlib.h>
#include <stdio.h>
void reset_hw_params(snd_pcm_t *handle, snd_pcm_hw_params_t *params)
{
    // close PCM device
    snd_pcm_close(handle);

    snd_pcm_open(&handle, "MIC2_SWSRC_IN", SND_PCM_STREAM_PLAYBACK, 0);

    snd_pcm_hw_params_alloca(&params);
    // snd_pcm_hw_params_init(params);
}
int main()
{
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    int err;

    unsigned int buffer_time = 10000;     // 10 ms
    unsigned long buffer_size = 1; // 
    unsigned long period_size = 1; //
    unsigned int buffer_time_tmp = 10000; // 10 ms
    for (int i = 0; i < 10000; i++)
    {
        if ((err = snd_pcm_open(&handle, "MIC2_SWSRC_IN", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
        {
            fprintf(stderr, "Error opening PCM device: %s\n", snd_strerror(err));
            return 1;
        }

        snd_pcm_hw_params_alloca(&params);

        if ((err = snd_pcm_hw_params_any(handle, params)) < 0)
        {
            fprintf(stderr, "Error initializing hardware parameters: %s\n", snd_strerror(err));
            snd_pcm_close(handle);
            return 1;
        }

        if ((err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
        {
            fprintf(stderr, "Error setting access type: %s\n", snd_strerror(err));
            snd_pcm_close(handle);
            return 1;
        }

        if ((err = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE)) < 0)
        {
            fprintf(stderr, "Error setting format: %s\n", snd_strerror(err));
            snd_pcm_close(handle);
            return 1;
        }

        unsigned int channels = 1;
        if ((err = snd_pcm_hw_params_set_channels(handle, params, channels)) < 0)
        {
            fprintf(stderr, "Error setting channels: %s\n", snd_strerror(err));
            snd_pcm_close(handle);
            return 1;
        }

        unsigned int rate = 22050;
        if ((err = snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0)) < 0)
        {
            fprintf(stderr, "Error setting rate: %s\n", snd_strerror(err));
            snd_pcm_close(handle);
            return 1;
        }

        printf("Set buffer time %u\n", buffer_time);
        buffer_time_tmp = buffer_time;
        // printf("TMP buffer-time %u\n", buffer_time_tmp);
        if ((err = snd_pcm_hw_params_set_buffer_time_near(handle, params, &buffer_time, 0)) < 0)
        {
            // fprintf(stderr, "Error setting buffer time: %s\n", snd_strerror(err));
            printf("Invalid buffer-time %u\n", buffer_time);
            // snd_pcm_close(handle);
            // return 1;
        }
        else
        {
            // buffer_time_tmp = buffer_time;
            (void)snd_pcm_hw_params_get_buffer_time(params, &buffer_time, NULL);
            printf("Support buffer time %u\n", buffer_time);
        }

        if ((err = snd_pcm_hw_params_set_buffer_size_near(handle, params, &buffer_size)) < 0)
        {
            // fprintf(stderr, "Error setting buffer time: %s\n", snd_strerror(err));
            printf("Invalid buffer-size %lu\n", buffer_size);
            // snd_pcm_close(handle);
            // return 1;
        }
        else
        {
            // buffer_time_tmp = buffer_time;
            (void)snd_pcm_hw_params_get_buffer_size(params, &buffer_size);
            printf("Support buffer size %lu\n", buffer_size);
        }

        if ((err = snd_pcm_hw_params_set_period_size_near(handle, params, &period_size, NULL)) < 0)
        {
            // fprintf(stderr, "Error setting buffer time: %s\n", snd_strerror(err));
            printf("Invalid period_size %lu\n", period_size);
            // snd_pcm_close(handle);
            // return 1;
        }
        else
        {
            // buffer_time_tmp = buffer_time;
            (void)snd_pcm_hw_params_get_period_size(params, &period_size,NULL);
            printf("Support period_size %lu\n", period_size);
        }



        buffer_time = buffer_time_tmp + 10;//10us
        snd_pcm_close(handle);
    }

    if ((err = snd_pcm_hw_params(handle, params)) < 0)
    {
        fprintf(stderr, "Error applying hardware parameters: %s\n", snd_strerror(err));
        snd_pcm_close(handle);
        return 1;
    }

    printf("Hardware parameters set successfully.\n");

    snd_pcm_close(handle);
    return 0;
}
