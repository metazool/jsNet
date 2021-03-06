
void Filter::init (int netInstance, int channels, int filterSize) {

    Network* net = Network::getInstance(netInstance);

    switch (net->updateFnIndex) {
        case 1: // gain
            biasGain = 1;
            weightGain = NetUtil::createVolume<double>(channels, filterSize, filterSize, 1);
            break;
        case 2: // adagrad
        case 3: // rmsprop
        case 5: // adadelta
        case 6: // momentum
            biasCache = 0;
            weightsCache = NetUtil::createVolume<double>(channels, filterSize, filterSize, 0);

            if (net->updateFnIndex == 5) {
                adadeltaBiasCache = 0;
                adadeltaCache = NetUtil::createVolume<double>(channels, filterSize, filterSize, 0);
            }
            break;
        case 4: // adam
            m = 0;
            v = 0;
            break;
    }

    if (net->activation == &NetMath::lrelu<Neuron>) {
        lreluSlope = net->lreluSlope;
    } else if (net->activation == &NetMath::rrelu<Neuron>) {
        rreluSlope = ((double) rand() / (RAND_MAX))/5 - 0.1;
    } else if (net->activation == &NetMath::elu<Neuron>) {
        eluAlpha = net->eluAlpha;
    }
}